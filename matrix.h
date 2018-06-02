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
    Matrix ();                     // Construtor (padrao)
    Matrix (int _rows, int _cols); // Construtor (matriz de zeros)
    Matrix (char *path);           // Construtor (le a matriz do arquivo path)
    void show ();                  // Exibe a matriz
    void save (char *path);        // Salva a matrix no arquivo path
    // Divide a matriz em vertical*horizontal submatrizes/blocos
    vector<Matrix> divide (int vertical, int horizontal);
private:
    void zeros ();                 // Inicializa a matriz com zeros
};

// Calcula a quantidade necessaria de blocos na vertical e na horizontal
// com base no numero maximo permitido de blocos e de threads
void calculate_blocks (int  A_rows,     int  A_cols,       int  B_cols,
                       int *A_vertical, int *A_horizontal, int *B_horizontal);

// Devolve a matriz C = AB
Matrix MATRIX_mult (Matrix *A, Matrix *B, char implementation);

// Faz a multiplicacao C = AB sequencialmente
void sequential_mult (Matrix *A, Matrix *B, Matrix *C);

// Faz a multiplicacao C = AB usando OpenMP
void openmp_mult (Matrix *A, Matrix *B, Matrix *C);

// Faz a multiplicacao C = AB usando Pthreads
void pthreads_mult (Matrix *A, Matrix *B, Matrix *C);
void *MULT_thread (void *p_id);

#endif

/******************************************************************************/
