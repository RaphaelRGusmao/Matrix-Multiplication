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

// Fonte
#define UNDERLINE "\033[4m"    // Underline_
#define CYAN      "\033[36;1m" // Azul claro
#define GREEN     "\033[32;1m" // Verde
#define PINK      "\033[35;1m" // Rosa
#define YELLOW    "\033[33;1m" // Amarelo
#define END       "\033[0m"    // Para de pintar

#include "matrix.h"

// Matriz
class BlockMatrix {
public:
    Matrix *matrix;
    int rows;        // Numero de linhas
    int cols;        // Numero de colunas
    int block_rows;
    int block_cols;
    int origin_row_index;
    int origin_col_index;
    /**************************************************************************/
    BlockMatrix (Matrix *_matrix, int _block_rows, int _block_cols, int _origin_row_index, int _origin_col_index); // Construtor (uma matriz que é um block de outra matriz)
    void show ();                  // Exibe a matriz
    // BlockMatrix (int _rows, int _cols); // Construtor (cria uma matriz de zeros)
    // BlockMatrix (char *path);           // Construtor (le a matriz do arquivo path)
    // ~BlockMatrix ();                    // Destrutor
    // void save (char *path);        // Salva a matrix no arquivo path
// private:
    // void zeros ();                 // Inicializa a matriz com zeros
};

// // Devolve a matriz C = AB
// BlockMatrix MATRIX_mult (BlockMatrix *A, BlockMatrix *B, char implementation);

// // Faz a multiplicacao C = AB sequencialmente
// void sequencial_mult (BlockMatrix *A, BlockMatrix *B, BlockMatrix *C);

// // Faz a multiplicacao C = AB usando OpenMP
// void openmp_mult (BlockMatrix *A, BlockMatrix *B, BlockMatrix *C);

// // Faz a multiplicacao C = AB usando Pthreads
// void pthreads_mult (BlockMatrix *A, BlockMatrix *B, BlockMatrix *C);

#endif

/******************************************************************************/
