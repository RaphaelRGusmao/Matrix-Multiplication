/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                 Utilidades                                 *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

// #define DEBUG
#ifdef DEBUG
    #define D(X) X
#else
    #define D(X)
#endif

// Fonte
#define UNDERLINE "\033[4m"    // Underline_
#define CYAN      "\033[36;1m" // Azul claro
#define GREEN     "\033[32;1m" // Verde
#define PINK      "\033[35;1m" // Rosa
#define YELLOW    "\033[33;1m" // Amarelo
#define END       "\033[0m"    // Para de pintar

// Retorna o tempo atual em nanossegundos
uint64_t getTime ();

// TODO comentar funcionalidade
int mcd (int a, int b);

// Calcula o maximo divisor comum dos numeros a e b
int gcd (int a, int b);

// Calcula todos os divisores comuns dos numeros a e b
int commDiv (int a, int b);

// Calcula o minimo divisor comum dos numeros a e b
int lcd (int a, int b);

#endif

/******************************************************************************/
