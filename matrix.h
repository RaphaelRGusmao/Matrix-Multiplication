/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                   Matriz                                   *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

// Matriz
class Matrix {
public:
    double **matrix; // Matriz
    int rows;        // Numero de linhas
    int cols;        // Numero de colunas
    /**************************************************************************/
    Matrix ();                          // Construtor (padrao)
    Matrix (int _rows, int _cols);      // Construtor (matriz de zeros)
    Matrix (char *path);                // Construtor (le a matriz do arquivo path)
    void show ();                       // Exibe a matriz
    void save (char *path);             // Salva a matrix no arquivo path
    vector<Matrix> divide (int factor); // Divide a matriz em factor*factor partes
private:
    void zeros ();                      // Inicializa a matriz com zeros
};

// Devolve a matriz C = AB
Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation);

// Faz a adicao C = A + B sequencialmente
void sequencial_add (Matrix *A, Matrix *B, Matrix *C);

// Faz a multiplicacao C = AB sequencialmente
void sequencial_mult (Matrix *A, Matrix *B, Matrix *C);

// Faz a multiplicacao C = AB usando OpenMP
void openmp_mult (Matrix *A, Matrix *B, Matrix *C);

// Faz a multiplicacao C = AB usando Pthreads
void pthreads_mult (Matrix *A, Matrix *B, Matrix *C);
void *MULT_thread (void *p_id);

#endif

/******************************************************************************/
