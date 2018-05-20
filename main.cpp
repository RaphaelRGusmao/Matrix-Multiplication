/******************************************************************************
 *                               IME-USP (2018)                               *
 *           EP1 de MAC0219 Introdução à Computação Concorrente,              *
 *                       Paralela e Distribuída                               *
 *                                                                            *
 *                                 Principal                                  *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/
#include <bits/stdc++.h>
#include <stdint.h>
#include <time.h>
#include <iostream>
// #include <fstream>
#include "matrix_reader.h"
using namespace std;

// Variavel global que indica se deve ou nao imprimir o estado final do programa
static int silent = 0;

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
// Recebe os argumentos de implementacao, caminho para a matriz A, caminho para
// a matriz B, e caminho para a matriz C.
int main (int argc, char const *argv[])
{
    if (argc < 5) {
        printf("Número insuficientes de argumentos\n");
        return -1;
    }

    // ideia inicial: trazer as matrizes A e B inteiramente para a memória,
    // depois dividimos elas em blocos e criamos várias threads para multiplicar
    // cada bloco o juntar os resultados.

    double **a_matrix;
    double **b_matrix;
    // double **c_matrix;

    // a_matrix = read_matrix(argv[2]);
    BlockMatrix bmA = read_matrix(argv[2]);

    if (strcmp(argv[1], "p") == 0) {
        // multiplica as matrizes com pthreads
        // TODO
        cout << "fazer a multiplicacao usando pthreads\n";

    } else if (strcmp(argv[1], "o") == 0) {
        // faz com openMP
        // TODO
        cout << "fazer a multiplicacao usando openMP\n";
    }

    bmA.destroy();

    cout << "fim\n";
}

/******************************************************************************/
