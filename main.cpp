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
#include "util.h"
#include "matrix.h"
using namespace std;

/******************************************************************************/
// Funcao principal
// Argumentos:
// Implementation: "p" = Pthreads, "o" = OpenMP, "s" = sequencial
// matrix_A: caminho da matriz A
// matrix_B: caminho da matriz B
// matrix_C: caminho da matriz C
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

    D(cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ START ]" << END << endl;)
    uint64_t start = getTime();

        Matrix C = MATRIX_mult(&A, &B, implementation);

    uint64_t end = getTime();
    D(cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ END ]" << END << endl << endl;)

    D(cout << CYAN << "C:" << END << endl; C.show(); cout << endl;)

    uint64_t total_time = end - start;
    cout << GREEN << "Runtime: " << (double)(end-start)/1000000000 << " s" << END << endl;

    C.save(C_path);
}

/******************************************************************************/
