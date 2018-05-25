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
#include "block_matrix.h"
using namespace std;


/******************************************************************************/
BlockMatrix::BlockMatrix (Matrix *_matrix, int _block_rows, int _block_cols, int _origin_row_index, int _origin_col_index) {
    matrix = _matrix;
    block_rows = _block_rows;
    block_cols = _block_cols;
    origin_row_index = _origin_row_index;
    origin_col_index = _origin_col_index;
}


/******************************************************************************/
// BlockMatrix::~BlockMatrix ()
// {
//     // matrix->~Matrix(); // Delegation
//     delete[] matrix;
// }

/******************************************************************************/
void BlockMatrix::show ()
{
    for (int i = 0; i < block_rows; i++) {
        for (int j = 0; j < block_cols; j++) {
            cout << matrix->matrix[origin_row_index + i][origin_col_index + j] << "\t";
        }
        cout << endl;
    }
}

/******************************************************************************/
// void BlockMatrix::save (char *path)
// {
//     ofstream file(path);
//     if (!file.is_open()) {
//         cout << YELLOW << "Erro ao salvar a matriz (" << path << ")" << END << endl;
//         exit(1);
//     }
//     file << rows << " " << cols << endl;
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             if (matrix[i][j]) {
//                 file << i+1 << " " << j+1 << " " << matrix[i][j] << endl;
//             }
//         }
//     }
//     file.close();
// }

/******************************************************************************/
// void BlockMatrix::zeros ()
// {
//     matrix = new double*[rows];
//     matrix[0] = new double[rows*cols];
    

//     memset(matrix[0], 0, rows*cols*sizeof(*matrix[0])); //TODO mudar isso
//     for (int i = 1; i < rows; i++) {
//         matrix[i] = matrix[0] + i * cols;
//     }

//     // for (int i = 0; i < rows; i++) {
//     // 	printf("[");
//     // 	for (int j = 0; j < cols; j++) {
//     // 		printf("%.2lf, ", matrix[i][j]);
//     // 	}
//     // 	printf(" ]\n");
//     // }
// }
