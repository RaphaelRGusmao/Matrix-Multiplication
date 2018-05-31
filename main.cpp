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

// #define DEBUG

#ifdef DEBUG
    #define D(X) X
#else
    #define D(X)
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
 
// Function to calculate all common divisors
// of two given numbers
// a, b --> input integer numbers
int commDiv(int a,int b)
{
    const int MAX_DIVISORS = 20;

    // find gcd of a,b
    int n = gcd(a, b);
    
    int *divisors = new int[MAX_DIVISORS];

    // Count divisors of n.
    int result = 0;
    for (int i=1; i<=sqrt(n); i++)
    {
        // if 'i' is factor of n
        if (n%i==0)
        {
            // check if divisors are equal
            if (n/i == i) {
                result += 1;    
                if (result < MAX_DIVISORS) divisors[result] = i;
            }
            else {
                if (result < MAX_DIVISORS-1) {
                    divisors[result+1] = i;
                    divisors[result+2] = n/i;
                }
                result += 2;
            }
        }
    }

    for (int i = 0; i < result; i++) {
        printf("%d é difisor comum de %d e %d\n", divisors[i], a, b);
    }

    return result;
}

int lcd(int a, int b) {
    int n = gcd(a, b);
    // printf("gcd %d e %d é: %d \n", a, b, n);
    for (int i=2; i<=n; i++) {
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
void sequencial_block_mult (BlockMatrix *A, BlockMatrix *B, BlockMatrix *C)
{
    // printf("A->origin_row_index: %d, A->block_rows: %d\n", A->origin_row_index, A->block_rows);
    // printf("A->origin_col_index: %d, A->block_cols: %d\n", A->origin_col_index, A->block_cols);
    // printf("B->origin_row_index: %d, B->block_rows: %d\n", B->origin_row_index, B->block_rows);
    // printf("B->origin_col_index: %d, B->block_cols: %d\n", B->origin_col_index, B->block_cols);
    for (int i = 0; i < A->block_rows; i++) {
        for (int j = 0; j < B->block_cols; j++) {
            for (int k = 0; k < A->block_cols; k++) {
                // printf("A->origin_col_index: %d, k: %d\n", A->origin_col_index, k);
                C->matrix->matrix[A->origin_row_index + i][B->origin_col_index + j] += 
                A->matrix->matrix[A->origin_row_index +i][A->origin_col_index + k] 
                * B->matrix->matrix[A->origin_col_index + k][B->origin_col_index + j];
            }
        }
    }
}


/******************************************************************************/
void openmp_mult (Matrix *A, Matrix *B, Matrix *C)
{

    D(printf("A->rows: %d\n", A->rows);)
    D(printf("A->cols: %d\n", A->cols);)
    D(printf("B->rows: %d\n", B->rows);)
    D(printf("B->cols: %d\n", B->cols);)

    int T = 2; //200;
    size_t p;
    double t0, t1;
    omp_lock_t mutex;
    omp_init_lock(&mutex);

    t0 = omp_get_wtime();

    // dividir pelo mmc das dimensões
    int b_a = lcd(A->rows, A->cols);
    // int b_a = lcd(A->cols, A->rows);
    // printf("b_a %d\n", b_a);
    
    // Altura de cada um dos blocos da matriz A
    int A_block_high = b_a;
    D(printf("A_block_high: %d\n", A_block_high);)
    
    // Comprimento de cada um dos blocos da matriz A e também altura de 
    // cada um dos blocos da matriz B
    int A_block_lenght = lcd(A->cols, B->rows);
    int B_block_high = A_block_lenght;
    D(printf("A_block_lenght = B_block_high: %d\n", A_block_lenght);)

    // Comprimento de cada um dos blocos da matriz B
    int b_b = lcd(B->rows, B->cols);
    // int B_block_lenght = B->cols / b_b;
    int B_block_lenght = b_b;
    D(printf("B_block_lenght: %d\n", B_block_lenght);)


    D(printf("Blocos das matrizes:\n");)
    for (int j = 0; j < B->cols / B_block_lenght; j++) {
        for (int i = 0; i < A->rows / A_block_high; i++) {
            BlockMatrix blockC(C, A_block_high, B_block_lenght, i * A_block_high, j * B_block_lenght);
            for (int k = 0; k < A->cols / A_block_lenght; k++) {
                D(printf("BlocoA [%d, %d]: \n", i, k);)
                BlockMatrix blockA(A, A_block_high, A_block_lenght, i * A_block_high, k * A_block_lenght);
                D(blockA.show();)
                D(printf("BlocoB [%d, %d]: \n", k, j);)
                BlockMatrix blockB(B, B_block_high, B_block_lenght, k * B_block_high, j * B_block_lenght);
                D(blockB.show();)
                // Multiplicar as matrizes e armazena na matriz (bloco) C
                // blockC = blockC + blockA * blockB
                sequencial_block_mult(&blockA, &blockB, &blockC);
            }
            D(printf("###############\n");)
            D(printf("BlocoC [%d, %d]: \n", i, j);)
            D(blockC.show();)
            D(printf("###############\n");)
        }
    }


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
    // Matrix C(A->rows, B->cols); //TODO o construtor inicializa C com zeros. Isso não é necessário
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


int test() {

    const char* test1 = "matrix/test1.txt";
    const char* test2 = "matrix/test2.txt";

    Matrix A((char*) test1);
    Matrix B((char*) test2);

    Matrix R(5, 7, false);

    double **result = new double*[5];
    result[0] = new double[5*7];
    double row1[7] = {2,   5,   20,  1,   0,   0,   0};
    double row2[7] = {0,   8,   10,  0,   0,   0,   0};
    double row3[7] = {0,   0,   2,   0,   0,   0,   0};
    double row4[7] = {0,   0,   0,   0,   0,   0,   0};
    double row5[7] = {0,   0,   8,   0,   0,   0,   0};
    result[0] = row1;
    result[1] = row2;
    result[2] = row3;
    result[3] = row4;
    result[4] = row5;

    // double result[5][7] = {
    // 2,   5,   20,  1,   0,   0,   0,
    // 0,   8,   10,  0,   0,   0,   0,
    // 0,   0,   2,   0,   0,   0,   0,
    // 0,   0,   0,   0,   0,   0,   0,
    // 0,   0,   8,   0,   0,   0,   0
    // };

    R.matrix = result;

    Matrix C = MATRIX_mult(&A, &B, 's');

    if (C.equal(&R)) {
        cout << "Passou no teste sequencial\n";
    } else {
        cout << "FALHOU no teste sequencial\n";
    }

    // C = MATRIX_mult(&A, &B, 'o');

    // if (C.equal(&R)) {
    //     cout << "Passou no teste OpenMP\n";
    // } else {
    //     cout << "FALHOU no teste OpenMP\n";
    // }

    // Matrix C = MATRIX_mult(&A, &B, 'p');

    cout << "fim dos testes\n";
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
        if (A.cols != B.rows) {
            cout << "Matriz A tem numero de colunas (" << A.cols << ") diferente do numero de linhas da matriz B (" << B.rows << ").\n";
            //TODO tem que chamar o destrutor das matrizes A e B?
            return 0;
        }

        Matrix C = MATRIX_mult(&A, &B, implementation);

    uint64_t finish = getTime();
    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]" << END << endl << endl;

    D(cout << CYAN << "C:" << END << endl; C.show(); cout << endl;)

    uint64_t total_time = finish - beginning;
    cout << GREEN << "Tempo de execucao: " << finish - beginning << " ns" << END << endl;

    C.save(C_path);

    test();
}

/******************************************************************************/
