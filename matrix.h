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

// Fonte
#define UNDERLINE "\033[4m"    // Underline_
#define CYAN      "\033[36;1m" // Azul claro
#define GREEN     "\033[32;1m" // Verde
#define PINK      "\033[35;1m" // Rosa
#define YELLOW    "\033[33;1m" // Amarelo
#define END       "\033[0m"    // Para de pintar

// Matriz
class Matrix {
public:
    double **matrix; // Matriz
    int rows;        // Numero de linhas
    int cols;        // Numero de colunas
    /**************************************************************************/
    Matrix (int _rows, int _cols); // Construtor (cria uma matriz de zeros)
    Matrix (int _rows, int _cols, bool _zeros); // Construtor (cria uma matriz vazia se _zeros for false)
    Matrix (char *path);           // Construtor (le a matriz do arquivo path)
    ~Matrix ();                    // Destrutor
    void show ();                  // Exibe a matriz
    void save (char *path);        // Salva a matrix no arquivo path
    int equal(Matrix *other);
private:
    void init(int _rows, int _cols); // Inicializa a matriz sem valores
    void zeros ();                 // Preenche a matriz com zeros
};

// // Devolve a matriz C = AB
// Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation);

// // Faz a multiplicacao C = AB sequencialmente
// void sequencial_mult (Matrix *A, Matrix *B, Matrix *C);

// // Faz a multiplicacao C = AB usando OpenMP
// void openmp_mult (Matrix *A, Matrix *B, Matrix *C);

// // Faz a multiplicacao C = AB usando Pthreads
// void pthreads_mult (Matrix *A, Matrix *B, Matrix *C);

#endif

/******************************************************************************/
