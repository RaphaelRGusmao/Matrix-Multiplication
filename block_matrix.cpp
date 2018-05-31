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
