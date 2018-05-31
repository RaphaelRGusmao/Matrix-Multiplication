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
#include <omp.h>
#include "util.h"
#include "matrix.h"
using namespace std;

/******************************************************************************/
Matrix::Matrix ()
{}

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
vector<Matrix> Matrix::divide (int factor)
{
    vector<Matrix> matrix_blocks;
    int x = factor;
    int y = factor;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            Matrix block;
            block.rows = rows/y;
            block.cols = cols/x;
            block.matrix = new double*[block.rows];
            for (int k = 0; k < block.rows; k++) {
                block.matrix[k] = matrix[0] + i*block.rows*cols + j*block.cols + k*cols;
            }
            matrix_blocks.push_back(block);
        }
    }
    return matrix_blocks;
}

/******************************************************************************/
void Matrix::zeros ()
{
	matrix = new double*[rows];
    matrix[0] = (double*)calloc(rows*cols, sizeof(*matrix[0]));
    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i*cols;
    }
}

/******************************************************************************/
vector<Matrix> A_blocks; // Submatrizes de A
vector<Matrix> B_blocks; // Submatrizes de B
vector<Matrix> C_blocks; // Submatrizes de C
Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation)
{
    if (A->cols != B->rows) {
        cout << YELLOW << "The matrices are not compatible" << END << endl;
        exit(1);
    }
    Matrix C(A->rows, B->cols);
    switch (implementation) {
        case 's':
            cout << UNDERLINE << CYAN << "Sequencial" << END << endl << endl;
            sequencial_mult(A, B, &C);
            break;
        case 'o':
            cout << UNDERLINE << CYAN << "OpenMP" << END << endl << endl;
            openmp_mult(A, B, &C);
            break;
        case 'p':
        default:
            cout << UNDERLINE << CYAN << "Pthreads" << END << endl << endl;
            pthreads_mult(A, B, &C);
            break;
    }
    return C;
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
void sequencial_add (Matrix *A, Matrix *B, Matrix *C)
{
    for (int i = 0; i < C->rows; i++) {
        for (int j = 0; j < C->cols; j++) {
            C->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }
}

/******************************************************************************/
void openmp_mult (Matrix *A, Matrix *B, Matrix *C)
{
    // D(printf("A->rows: %d\n", A->rows);)
    // D(printf("A->cols: %d\n", A->cols);)
    // D(printf("B->rows: %d\n", B->rows);)
    // D(printf("B->cols: %d\n", B->cols);)
    //
    // size_t T = 20;
    //
    // // int T = 20; //200;
    // size_t p;
    // double t0, t1;
    // omp_lock_t mutex;
    // omp_init_lock(&mutex);
    //
    // t0 = omp_get_wtime();
    //
    // // dividir pelo mmc das dimensões
    // int b_a = lcd(A->rows, A->cols);
    // // int b_a = lcd(A->cols, A->rows);
    // // printf("b_a %d\n", b_a);
    //
    // // Altura de cada um dos blocos da matriz A
    // int A_block_high = b_a;
    // D(printf("A_block_high: %d\n", A_block_high);)
    //
    // // Comprimento de cada um dos blocos da matriz A e também altura de
    // // cada um dos blocos da matriz B
    // int A_block_lenght = lcd(A->cols, B->rows);
    // int B_block_high = A_block_lenght;
    // D(printf("A_block_lenght = B_block_high: %d\n", A_block_lenght);)
    //
    // // Comprimento de cada um dos blocos da matriz B
    // int b_b = lcd(B->rows, B->cols);
    // // int B_block_lenght = B->cols / b_b;
    // int B_block_lenght = b_b;
    // D(printf("B_block_lenght: %d\n", B_block_lenght);)
    //
    // D(printf("Blocos das matrizes:\n");)
    // // #pragma omp parallel for collapse (2) private(p)
    // #pragma omp parallel for collapse (2) private(p) num_threads(T)
    // for (int j = 0; j < B->cols / B_block_lenght; j++) {
    //     for (int i = 0; i < A->rows / A_block_high; i++) {
    //         BlockMatrix blockC(C, A_block_high, B_block_lenght, i * A_block_high, j * B_block_lenght);
    //         for (int k = 0; k < A->cols / A_block_lenght; k++) {
    //             D(printf("BlocoA [%d, %d]: \n", i, k);)
    //             BlockMatrix blockA(A, A_block_high, A_block_lenght, i * A_block_high, k * A_block_lenght);
    //             D(blockA.show();)
    //             D(printf("BlocoB [%d, %d]: \n", k, j);)
    //             BlockMatrix blockB(B, B_block_high, B_block_lenght, k * B_block_high, j * B_block_lenght);
    //             D(blockB.show();)
    //             // Multiplicar as matrizes e armazena na matriz (bloco) C
    //             // blockC = blockC + blockA * blockB
    //             sequencial_block_mult(&blockA, &blockB, &blockC);
    //         }
    //         D(printf("###############\n");)
    //         D(printf("BlocoC [%d, %d]: \n", i, j);)
    //         D(blockC.show();)
    //         D(printf("###############\n");)
    //     }
    // }
    //
    // t1 = omp_get_wtime();
    //
    // printf("tempo: %lf\n", t1-t0);
    // cout << "Tempo de execucao: " << (t1*1000000000-t0*1000000000) << " nanossegundos" << endl;
	// // TODO O tempo ja eh calculado na main, nao precisa calcular aqui
}

/******************************************************************************/
void pthreads_mult (Matrix *A, Matrix *B, Matrix *C)
{
	int factor = gcd(gcd(A->rows, A->cols), B->cols);

	// Divide as matrizes em submatrizes/blocos
    A_blocks = A->divide(factor);
    B_blocks = B->divide(factor);
    C_blocks = C->divide(factor);

    // Cria as threads
    vector<pthread_t> threads(factor*factor);
    for (long i = 0; i < factor*factor; i++) {
        if (pthread_create(&threads[i], NULL, MULT_thread, (void*)i)) {
           cout << YELLOW << "Error creating thread " << i << END << endl;
           exit(1);
        }
    }

    // Espera as threads terminarem de executar
    for (int i = 0; i < factor*factor; i++) {
        if (pthread_join(threads[i], NULL)) {
           cout << YELLOW << "Error joining thread " << i << END << endl;
           exit(1);
        }
    }
}

/******************************************************************************/
void *MULT_thread (void *p_id)
{
    long id = (long)p_id;
    int factor = (int)sqrt(C_blocks.size());
    int i = id/factor;
    int j = id%factor;
    for (int k = 0; k < factor; k++) {
        Matrix AB(C_blocks[id].rows, C_blocks[id].cols);
        sequencial_mult(&A_blocks[i*factor + k], &B_blocks[k*factor + j], &AB);
        sequencial_add(&C_blocks[id], &AB, &C_blocks[id]);
    }
}

/******************************************************************************/
