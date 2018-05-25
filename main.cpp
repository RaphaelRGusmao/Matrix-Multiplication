/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                 Principal                                  *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include <stdint.h>
// #include "matrix.h"
#include <omp.h>
#include "block_matrix.h"
using namespace std;

#define DEBUG

#ifdef DEBUG
    #define D(X) X
#endif

/******************************************************************************/
// Retorna o tempo atual em nanossegundos
uint64_t getTime ()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
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
    int A_block_lenght = lcd(A->cols, B->rows);
    // int A_block_lenght = b_a;
    int B_block_high = A_block_lenght;
    printf("A_block_lenght: %d\n", A_block_lenght);
    // Comprimento de cada um dos blocos da matriz B
    // int B_block_lenght = floor(1.0 * B->cols / T);
    int b_b = lcd(B->rows, B->cols);
    // int B_block_lenght = B->cols / b_b;
    int B_block_lenght = b_b;
    printf("B_block_lenght: %d\n", B_block_lenght);


    // BlockMatrix *b0 = new BlockMatrix(A, A_block_high, A_block_lenght, 0, 0);
    // BlockMatrix b0(A, A_block_high, A_block_lenght, 0, 0);
    // b0.show();


    // printf("Blocos da matriz A\n");

    printf("Blocos das matrizes:\n");
    for (int i = 0; i < A->rows / A_block_high; i++) {
        for (int j = 0; j < B->cols / B_block_lenght; j++) {
            BlockMatrix blockC(C, A_block_high, B_block_lenght, i * A_block_high, j * B_block_lenght);
            for (int k = 0; k < A->cols / A_block_lenght; k++) {
                printf("BlocoA [%d, %d]: \n", i, j);
                BlockMatrix blockA(A, A_block_high, A_block_lenght, i * A_block_high, k * A_block_lenght);
                blockA.show(); 
                printf("BlocoB [%d, %d]: \n", k, j);
                BlockMatrix blockB(B, B_block_high, B_block_lenght, k * B_block_high, j * B_block_lenght);
                blockB.show();
                printf("--------------\n");
                // TODO multiplicar as matrizes e armazenar na (bloco)matriz C
                // matriz_soma[r, t] += blockA * blockB;
                // C = C + blockA * blockB
            }
            printf("BlocoC [%d, %d]: \n", i, j);
            blockC.show();
            printf("###############\n");
        }
    }

    // dividir pelo mdc das dimensões

    #pragma omp parallel for private(p) num_threads(T)
  //   for (int i = p * A_block_high; i < (p+1) * A_block_high; i++) {
  //    double sum = 0;
  //    for (int j = p * A_block_lenght; j < (p+1) * A_block_lenght; j++) {
  //        // sum += A->matrix[i][j] * B->matrix[i][j];
        //  // multiplicar matrizes
  //        printf("Block A[%d .. %d][%d .. %d] * Block B[%d .. %d][%d .. %d]\n", 
  //                        i, i + A_block_lenght, i, i + A_block_high, j, j + B_block_lenght, j, j + B_block_high);
  //    }
        // // C.matrix[i][j] = sum;
        // printf("\n");
  //   }


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
// Ideia inicial: trazer as matrizes A e B inteiramente para a  memória,  depois
// dividimos elas em blocos e criamos várias threads para multiplicar cada bloco
// e juntar os resultados.
Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation)
{
    Matrix C(A->rows, B->cols); //TODO o construtor inicializa C com zeros. Isso não é necessário
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


/******************************************************************************/
// Funcao principal
// Argumentos:
// matrix_A: caminho da matriz A
// matrix_A: caminho da matriz B
// matrix_A: caminho da matriz C
// Implementation: "p" = Pthreads, "o" = OpenMP, "s" = sequencial
//                 (argumento opcional, "p" eh o padrao)
int main (int argc, char **argv)
{
    if (argc != 4 && argc != 5) {
        cout << "Usage: ./main <Implementation> <matrix_A> <matrix_B> <matrix_C>" << endl;
        return 1;
    }
    char implementation = 'p'; if (argc == 5) implementation = argv[1][0];
    char *A_path = argv[2];
    char *B_path = argv[3];
    char *C_path = argv[4];

    Matrix A(A_path);
    D(cout << CYAN << "A:" << END << endl; A.show(); cout << endl;)

    Matrix B(B_path);
    D(cout << CYAN << "B:" << END << endl; B.show(); cout << endl;)

    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Inicio ]" << END << endl;
    uint64_t beginning = getTime();

        Matrix C = MATRIX_mult(&A, &B, implementation);

    uint64_t finish = getTime();
    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]" << END << endl << endl;

    D(cout << CYAN << "C:" << END << endl; C.show(); cout << endl;)

    uint64_t total_time = finish - beginning;
    cout << GREEN << "Tempo de execucao: " << finish - beginning << " ns" << END << endl;

    C.save(C_path);
}

/******************************************************************************/
