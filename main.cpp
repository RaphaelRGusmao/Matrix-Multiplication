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

#define DEBUG

#ifdef DEBUG
    #define D(X) X
#endif

/******************************************************************************/
// Retorna o tempo atual em nanossegundos
uint64_t getTime ()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}

/******************************************************************************/
// Funcao principal
// Argumentos:
// matrix_A: caminho da matriz A
// matrix_A: caminho da matriz B
// matrix_A: caminho da matriz C
// Implementation: "p" = Pthreads, "o" = OpenMP, "s" = sequencial
//                 (argumento opcional, "p" eh o padrao)
int main (int argc, char **argv)
{
    if (argc != 4 && argc != 5) {
        cout << "Usage: ./main <Implementation> <matrix_A> <matrix_B> <matrix_C>" << endl;
        return 1;
    }
    char implementation = 'p'; if (argc == 5) implementation = argv[1][0];
    char *A_path = argv[2];
    char *B_path = argv[3];
    char *C_path = argv[4];

    Matrix A(A_path);
    D(cout << CYAN << "A:" << END << endl; A.show(); cout << endl;)

    Matrix B(B_path);
    D(cout << CYAN << "B:" << END << endl; B.show(); cout << endl;)

    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Inicio ]" << END << endl;
    uint64_t beginning = getTime();

        Matrix C = MATRIX_mult(&A, &B, implementation);

    uint64_t finish = getTime();
    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]" << END << endl << endl;

    D(cout << CYAN << "C:" << END << endl; C.show(); cout << endl;)

    uint64_t total_time = finish - beginning;
    cout << GREEN << "Tempo de execucao: " << finish - beginning << " ns" << END << endl;

    C.save(C_path);
}

/******************************************************************************/
