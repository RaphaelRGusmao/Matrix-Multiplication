#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "matrix_reader.h"
using namespace std;

double **read_matrix(const char *path) {
    ofstream matrix_file;
    matrix_file.open (path);
    double **matrix = NULL;
    if (matrix_file.is_open()) {
        cout << "motar a matriz a partir dos dados do arquivo\n";
        int lines;
        int columns;

        
    } else cout << "Unable to open file";
    matrix_file.close(); 
    return matrix;
}

void print_matrix(int lines, int columns, double **matrix) {

    for (int i = 0; i < lines; i++)    {
        for (int j = 0; j < columns; j++) {
            // 
            printf("%f ", matrix[i][j]);
        }
        cout << "\n";
    }
}
