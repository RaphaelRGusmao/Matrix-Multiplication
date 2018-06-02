/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                 Principal                                  *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include <stdint.h>
#include "matrix.h"
using namespace std;

// #define DEBUG
#ifdef DEBUG
    #define D(X) X
#else
    #define D(X)
#endif

/******************************************************************************/
// Retorna o tempo atual em nanossegundos
uint64_t get_time ()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}

/******************************************************************************/
// Funcao principal
// Argumentos:
// implementation: "p" = Pthreads, "o" = OpenMP, "s" = Sequencial
// matrix_A: caminho da matriz A
// matrix_B: caminho da matriz B
// matrix_C: caminho da matriz C
int main (int argc, char **argv)
{
    if (argc != 4 && argc != 5) {
        cout << "Usage: ./main <implementation> <matrix_A> <matrix_B> <matrix_C>" << endl;
        return 1;
    }
    char implementation = 'p'; if (argc == 5) implementation = argv[1][0];
    char *A_path = argv[2];
    char *B_path = argv[3];
    char *C_path = argv[4];

    cout << CYAN << "Reading inputs..." << endl << endl;;

    Matrix A(A_path);
    D(cout << CYAN << "A:" << END << endl; A.show(); cout << endl;)

    Matrix B(B_path);
    D(cout << CYAN << "B:" << END << endl; B.show(); cout << endl;)

    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ START ]" << END << endl;
    uint64_t start = get_time();

        Matrix C = MATRIX_mult(&A, &B, implementation);

    uint64_t end = get_time();
    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ END ]" << END << endl;

    if (C.matrix != NULL) {
        D(cout << CYAN << "C:" << END << endl; C.show(); cout << endl;)

        uint64_t total_time = end - start;
        cout << GREEN << "Multiplication time: " << (double)(end-start)/1000000000 << " s" << END << endl << endl;

        cout << CYAN << "Saving output..." << END << endl;

        C.save(C_path);
    }
}

/******************************************************************************/
