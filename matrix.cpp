/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                   Matriz                                   *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include "matrix.h"
#include <omp.h>
using namespace std;

/******************************************************************************/
Matrix::Matrix (int _rows, int _cols)
{
    rows = _rows;
    cols = _cols;
    this->zeros();
}

/******************************************************************************/
Matrix::Matrix (char *path)
{
    ifstream file(path);
    if (!file.is_open()) {
        cout << YELLOW << "Erro ao ler a matriz (" << path << ")" << END << endl;
        exit(1);
    }
    file >> rows >> cols;
    this->zeros();
    while (!file.eof()) {
        int i, j; double value;
        file >> i >> j >> value;
        matrix[i-1][j-1] = value;
    }
    file.close();
}

/******************************************************************************/
Matrix::~Matrix ()
{
    delete[] matrix;
}

/******************************************************************************/
void Matrix::show ()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

/******************************************************************************/
void Matrix::save (char *path)
{
    ofstream file(path);
    if (!file.is_open()) {
        cout << YELLOW << "Erro ao salvar a matriz (" << path << ")" << END << endl;
        exit(1);
    }
    file << rows << " " << cols << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j]) {
                file << i+1 << " " << j+1 << " " << matrix[i][j] << endl;
            }
        }
    }
    file.close();
}

/******************************************************************************/
void Matrix::zeros ()
{
    matrix = new double*[rows];
    matrix[0] = new double[rows*cols];
    

    memset(matrix[0], 0, rows*cols*sizeof(*matrix[0])); //TODO mudar isso
    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }

    // for (int i = 0; i < rows; i++) {
    // 	printf("[");
    // 	for (int j = 0; j < cols; j++) {
    // 		printf("%.2lf, ", matrix[i][j]);
    // 	}
    // 	printf(" ]\n");
    // }
}

/******************************************************************************/
// Ideia inicial: trazer as matrizes A e B inteiramente para a  memória,  depois
// dividimos elas em blocos e criamos várias threads para multiplicar cada bloco
// e juntar os resultados.
Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation)
{
    Matrix C(A->rows, B->cols);
    switch (implementation) {
        case 's':
            cout << "Sequencial" << endl;
            sequencial_mult(A, B, &C);
            break;
        case 'o':
            cout << "OpenMP" << endl;
            openmp_mult(A, B, &C);
            break;
        case 'p':
        default:
            cout << "Pthreads" << endl;
            pthreads_mult(A, B, &C);
            break;
    }
    return C;
}

int mcd(int a, int b) {
  int t;
  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}

// Function to calculate gcd of two numbers
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b%a, a);
}
 
// // Function to calculate all common divisors
// // of two given numbers
// // a, b --> input integer numbers
// int commDiv(int a,int b)
// {
//     // find gcd of a,b
//     int n = gcd(a, b);
 
//     // Count divisors of n.
//     int result = 0;
//     for (int i=1; i<=sqrt(n); i++)
//     {
//         // if 'i' is factor of n
//         if (n%i==0)
//         {
//             // check if divisors are equal
//             if (n/i == i)
//                 result += 1;
//             else
//                 result += 2;
//         }
//     }
//     return result;
// }

int lcd(int a, int b) {
	int n = gcd(a, b);
	for (int i=2; i<=sqrt(n); i++) {
		if (n % i == 0) return i;
	}
	return 1;
}

/******************************************************************************/
void sequencial_mult (Matrix *A, Matrix *B, Matrix *C)
{
    for (int i = 0; i < C->rows; i++) {
        for (int j = 0; j < C->cols; j++) {
            for (int k = 0; k < A->cols; k++) {
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }
}

/******************************************************************************/
void openmp_mult (Matrix *A, Matrix *B, Matrix *C)
{
    // TODO

	printf("A->rows: %d\n", A->rows);
	printf("A->cols: %d\n", A->cols);
	printf("B->rows: %d\n", B->rows);
	printf("B->cols: %d\n", B->cols);

    int T = 2; //200;
    size_t p;
    double t0, t1;
    omp_lock_t mutex;
    omp_init_lock(&mutex);

    t0 = omp_get_wtime();

    int b_a = lcd(A->rows, A->cols);
    // cout << "commDiv: ";
    // cout << lcd(A->rows, A->cols);
    printf("b_a %d\n", b_a);
    // Altura de cada um dos blocos da matriz A
    // int A_block_high = floor(1.0 * A->rows / T);
    // int A_block_high = A->rows / b_a;
    int A_block_high = b_a;
    printf("A_block_high: %d\n", A_block_high);
    // Comprimento de cada um dos blocos da matriz A e também altura de 
    // cada um dos blocos da matriz B
    // int A_block_lenght = floor(1.0 * A->cols / T);
    // int A_block_lenght = A->cols / b_a;
    int A_block_lenght = b_a;
    int B_block_high = A_block_lenght;
    printf("A_block_lenght: %d\n", A_block_lenght);
    // Comprimento de cada um dos blocos da matriz B
    // int B_block_lenght = floor(1.0 * B->cols / T);
    int b_b = lcd(B->rows, B->cols);
    // int B_block_lenght = B->cols / b_b;
    int B_block_lenght = b_b;
    printf("B_block_lenght: %d\n", B_block_lenght);

    // dividir pelo mdc das dimensões

    #pragma omp parallel for private(p) num_threads(T)
  //   for (int i = p * A_block_high; i < (p+1) * A_block_high; i++) {
  //   	double sum = 0;
  //   	for (int j = p * A_block_lenght; j < (p+1) * A_block_lenght; j++) {
  //   		// sum += A->matrix[i][j] * B->matrix[i][j];
		// 	// multiplicar matrizes
  //   		printf("Block A[%d .. %d][%d .. %d] * Block B[%d .. %d][%d .. %d]\n", 
  //   						i, i + A_block_lenght, i, i + A_block_high, j, j + B_block_lenght, j, j + B_block_high);
  //   	}
		// // C.matrix[i][j] = sum;
		// printf("\n");
  //   }

    /*
    for (int i = T - (A.cols % T); i < A_block_high; i++) {
    	for (int j = T - (B.rows % T); j < B_block_lenght; j++) {
    		// multiplicar matrizes
    		printf("Block A[%d .. %d][%d .. %d] * Block B[%d .. %d][%d .. %d]\n", i, i + , j, );
    		// printf("A[%.2lf, %.2lf] * B[%.2lf, %.2lf]\n", A.matrix[]);
    	}
    }
    */

    // for (i = 0; i < N; ++i) {
        // omp_set_lock(&mutex);
        // if (v[i] > max) {
        //     max = v[i];
        // }
        // omp_unset_lock(&mutex);
        // multiplicar as matrizes por blocos

	    // construir um bloco de matriz para cada uma das threads T
	    // Arxs * Bsxt = Crxt
    // }
    t1 = omp_get_wtime();

    // return (t1-t0);
    printf("tempo: %lf\n", t1-t0);

}

/******************************************************************************/
void pthreads_mult (Matrix *A, Matrix *B, Matrix *C)
{
    // TODO
}

/******************************************************************************/
