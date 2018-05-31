/******************************************************************************
 *                               IME-USP (2018)                               *
 *             MAC0219 - Programacao Concorrente e Paralela - EP1             *
 *                                                                            *
 *                                 Utilidades                                 *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include <stdint.h>
#include "util.h"
using namespace std;

/******************************************************************************/
uint64_t getTime ()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}

/******************************************************************************/
int mcd (int a, int b)
{
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/******************************************************************************/
int gcd (int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b%a, a);
}

/******************************************************************************/
int commDiv (int a, int b)
{
    const int MAX_DIVISORS = 20;
    int n = gcd(a, b);
    int *divisors = new int[MAX_DIVISORS];
    int result = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n%i == 0) {
            if (n/i == i) {
                result += 1;
                if (result < MAX_DIVISORS) divisors[result] = i;
            } else {
                if (result < MAX_DIVISORS - 1) {
                    divisors[result+1] = i;
                    divisors[result+2] = n/i;
                }
                result += 2;
            }
        }
    }
    for (int i = 0; i < result; i++) {
        printf("%d eh divisor comum de %d e %d\n", divisors[i], a, b);
    }
    return result;
}

/******************************************************************************/
int lcd (int a, int b)
{
    int n = gcd(a, b);
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) return i;
    }
    return 1;
}

/******************************************************************************/
