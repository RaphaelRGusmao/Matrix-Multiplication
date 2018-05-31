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
	this->init(_rows, _cols);
    this->zeros();
}

/******************************************************************************/
Matrix::Matrix (int _rows, int _cols, bool _zeros)
{
	this->init(_rows, _cols);
	if (_zeros) {
		this->zeros();
	} else {
		matrix[0] = (double*) malloc(rows*cols*sizeof(*matrix[0]));
	    for (int i = 1; i < rows; i++) {
	        matrix[i] = matrix[0] + i * cols;
	    }
	}
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
    matrix = new double*[rows];
    matrix[0] = new double[rows*cols];
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
int Matrix::equal(Matrix *other)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != other->matrix[i][j]) return 0;
		}
	}
	return 1;
}

/******************************************************************************/
void Matrix::init (int _rows, int _cols) {
    rows = _rows;
    cols = _cols;
    matrix = new double*[rows];
    matrix[0] = new double[rows*cols];
}

/******************************************************************************/
void Matrix::zeros ()
{
    // Troquei o uso do memset pelo calloc conforme esse post:
    // https://stackoverflow.com/questions/2688466/why-mallocmemset-is-slower-than-calloc
    // memset(matrix[0], 0, rows*cols*sizeof(*matrix[0])); 
    matrix[0] = (double*) calloc(rows*cols, sizeof(*matrix[0]));
    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }
}


/******************************************************************************/
