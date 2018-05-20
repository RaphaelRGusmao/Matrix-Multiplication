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
    memset(matrix[0], 0, rows*cols*sizeof(*matrix[0]));
    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }
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
}

/******************************************************************************/
void pthreads_mult (Matrix *A, Matrix *B, Matrix *C)
{
    // TODO
}

/******************************************************************************/
