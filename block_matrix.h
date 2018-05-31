/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                   Matriz                                   *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#ifndef BLOCK_MATRIX_H
#define BLOCK_MATRIX_H

#include "matrix.h"

// Matriz
class BlockMatrix {
public:
    Matrix *matrix;
    int rows; // Numero de linhas
    int cols; // Numero de colunas
    int block_rows;
    int block_cols;
    int origin_row_index;
    int origin_col_index;
    /**************************************************************************/
    // Construtor (uma matriz que é um block de outra matriz)
    BlockMatrix (Matrix *_matrix, int _block_rows, int _block_cols, int _origin_row_index, int _origin_col_index);
    void show (); // Exibe a matriz
};

void sequencial_block_mult (BlockMatrix *A, BlockMatrix *B, BlockMatrix *C);

#endif

/******************************************************************************/
