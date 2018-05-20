#include "block_matrix.h"



/******************************************************************************/
BlockMatrix::BlockMatrix (int _n_lines, int _n_columns, double **_matrix) {
    n_lines = _n_lines;
    n_columns = _n_columns;
    matrix = _matrix;
}


// /******************************************************************************/
// void BlockMatrix::set_val (int line, int column, double val) {
//     matrix[line][column] = val;
// }

// /******************************************************************************/
// double BlockMatrix::get_val (int line, int column) {
//     return matrix[line][column];
// }

// /******************************************************************************/
// int BlockMatrix::n_lines () {
//     return n_lines;
// }

// /******************************************************************************/
// int BlockMatrix::n_columns () {
//     return n_columns;
// }

/******************************************************************************/
void BlockMatrix::destroy () {
    for (int i = 0; i < n_lines; i++) {
        // free(matrix[i]);
        delete [] matrix[i];
    }
    // free(matrix);
    delete [] matrix;
}