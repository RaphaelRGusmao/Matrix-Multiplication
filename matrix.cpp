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
                file << i+1 << " " << j+1 << " " << std::fixed << std::setprecision(8) << matrix[i][j] << endl;
            }
        }
    }
    file.close();
}

/******************************************************************************/
vector<Matrix> Matrix::divide (int vertical, int horizontal)
{
    vector<Matrix> matrix_blocks;
    for (int i = 0; i < vertical; i++) {
        for (int j = 0; j < horizontal; j++) {
            Matrix block;
            block.rows = rows/vertical;
            block.cols = cols/horizontal;
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
void calculate_blocks (int  A_rows,     int  A_cols,       int  B_cols,
                       int *A_vertical, int *A_horizontal, int *B_horizontal)
{
    int max_blocks = 1024;
    int max_threads = 64;
    int max_sum = 0;
    for (int i = 1; i <= max_blocks; i++) {
        if (A_cols%i != 0) continue;
        // Divide A_cols e B_rows em i blocos
        int j, k;
        for (j = max_blocks/i; j > 0; j--) {
            if (j > sqrt(max_threads) || A_rows%j != 0) continue;
            // Divide A_rows em j blocos
            break;
        }
        for (k = max_blocks/i; k > 0; k--) {
            if (k > sqrt(max_threads) || B_cols%k != 0) continue;
            // Divide B_cols em k blocos
            break;
        }
        if (i*(j+k) > max_sum) {
            max_sum = i*(j+k);
            *A_horizontal = i;
            *A_vertical = j;
            *B_horizontal = k;
        }
    }
}

/******************************************************************************/
int A_vertical, A_horizontal, B_vertical, B_horizontal; // Numero de blocos
vector<Matrix> A_blocks; // Submatrizes de A
vector<Matrix> B_blocks; // Submatrizes de B
vector<Matrix> C_blocks; // Submatrizes de C
Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation)
{
    cout << "A(" <<  A->rows << " x " <<  A->cols << ") * "
         << "B(" <<  B->rows << " x " <<  B->cols << ") ";
    if (A->cols != B->rows) {
        cout << endl << YELLOW << "The matrices are not compatible" << END << endl;
        Matrix C;
        return C; // NULL
    }
    Matrix C(A->rows, B->cols);
    cout << "= C(" <<  C.rows  << " x " <<  C.cols  << ") "   << endl;
    switch (implementation) {
        case 's':
            cout << UNDERLINE << CYAN << "Sequential" << END << endl;
            cout << "Threads working: "<< CYAN << "1" << END << endl;
            sequential_mult(A, B, &C);
            break;
        case 'o':
            cout << UNDERLINE << CYAN << "OpenMP" << END << endl;
            openmp_mult(A, B, &C);
            break;
        case 'p':
        default:
            cout << UNDERLINE << CYAN << "Pthreads" << END << endl;
            pthreads_mult(A, B, &C);
            break;
    }
    return C;
}

/******************************************************************************/
void sequential_mult (Matrix *A, Matrix *B, Matrix *C)
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
    // Calcula os tamanhos dos blocos das matrizes
    calculate_blocks(A->rows,     A->cols,       B->cols,
                    &A_vertical, &A_horizontal, &B_horizontal);
    B_vertical = A_horizontal;
    int n_threads = A_vertical*B_horizontal;

    // Divide as matrizes em submatrizes/blocos
    A_blocks = A->divide(A_vertical, A_horizontal);
    B_blocks = B->divide(B_vertical, B_horizontal);
    C_blocks = C->divide(A_vertical, B_horizontal);
    cout << "Matrix A divided into " << CYAN << A_vertical << "*" << A_horizontal
         << " = " << A_vertical*A_horizontal << END " blocks" << endl;
    cout << "Matrix B divided into " << CYAN << B_vertical << "*" << B_horizontal
         << " = " << B_vertical*B_horizontal << END " blocks" << endl;
    cout << "Threads working: "      << CYAN << n_threads << END << endl;

    // OpenMP
    int id;
    #pragma omp parallel for private(id) num_threads(n_threads)
    for (id = 0; id < n_threads; id++) {
        int i = id/B_horizontal;
        int j = id%B_horizontal;
        for (int k = 0; k < A_horizontal; k++) {
            sequential_mult(&A_blocks[i*A_horizontal + k], &B_blocks[k*B_horizontal + j], &C_blocks[id]);
        }
    }
}

/******************************************************************************/
void pthreads_mult (Matrix *A, Matrix *B, Matrix *C)
{
    // Calcula os tamanhos dos blocos das matrizes
    calculate_blocks(A->rows,     A->cols,       B->cols,
                    &A_vertical, &A_horizontal, &B_horizontal);
    B_vertical = A_horizontal;
    int n_threads = A_vertical*B_horizontal;

    // Divide as matrizes em submatrizes/blocos
    A_blocks = A->divide(A_vertical, A_horizontal);
    B_blocks = B->divide(B_vertical, B_horizontal);
    C_blocks = C->divide(A_vertical, B_horizontal);
    cout << "Matrix A divided into " << CYAN << A_vertical << "*" << A_horizontal
         << " = " << A_vertical*A_horizontal << END " blocks" << endl;
    cout << "Matrix B divided into " << CYAN << B_vertical << "*" << B_horizontal
         << " = " << B_vertical*B_horizontal << END " blocks" << endl;
    cout << "Threads working: "      << CYAN << n_threads << END << endl;

    // Cria as threads
    vector<pthread_t> threads(n_threads);
    for (long i = 0; i < n_threads; i++) {
        if (pthread_create(&threads[i], NULL, MULT_thread, (void*)i)) {
            cout << YELLOW << "Error creating thread " << i << END << endl;
            exit(1);
        }
    }

    // Espera as threads terminarem de executar
    for (int i = 0; i < n_threads; i++) {
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
    int i = id/B_horizontal;
    int j = id%B_horizontal;
    for (int k = 0; k < A_horizontal; k++) {
        sequential_mult(&A_blocks[i*A_horizontal + k], &B_blocks[k*B_horizontal + j], &C_blocks[id]);
    }
}

/******************************************************************************/
