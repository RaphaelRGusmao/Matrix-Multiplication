#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "matrix_reader.h"
using namespace std;



void print_matrix(int lines, int columns, double **matrix) {

    for (int i = 0; i < lines; i++)    {
        for (int j = 0; j < columns; j++) {
            // 
            printf("%lf ", matrix[i][j]);
        }
        cout << "\n";
    }
}

void fill_previous(int prev_line, int prev_column, int line, int column, double **matrix, int lines, int columns) {
    int last_specified = columns * prev_line + prev_column;
    int actual_specified = columns * line + column;
    int i = actual_specified - 1;
    // printf("last_specified: %d, actual_specified: %d, i: %d\n", last_specified, actual_specified, i);
    while (i > last_specified) {
           // printf("changing [%d, %d], i: %d \n", i / columns, i % columns, i);
           matrix[i / columns][i % columns] = 0.0;
           i = i - 1;
    }
}

BlockMatrix read_matrix(const char *path) {

    // printf("path: %s\n", path);
    FILE *matrix_file;
    // double **matrix = NULL;
    BlockMatrix *bm;
    if ((matrix_file = fopen (path,"r")) != NULL) {
        cout << "montar a matriz a partir dos dados do arquivo\n";

        // Usei isso para ler todo o arquivo, soh para teste
        // char *line;
        // size_t len = 0;
        // int read;
        // while ( (read = getline(&line, &len, matrix_file)) != -1 ) {

        //     printf("%s", line);

        //     int line_n, column_n;
        //     double value;
        //     scanf("%d", &line_n, *line);
        //     scanf("%d", &column_n, *line);
        //     scanf("%lf", &value, *line);
        //     printf("line: %d, column: %d, value: %lf\n", line_n, column_n, value);
        // }

        int lines;
        int columns;
        fscanf (matrix_file, "%d", &lines);
        fscanf (matrix_file, "%d", &columns);

        printf("lines: %d, columns: %d\n", lines, columns);
        
        // matrix = malloc(lines * sizeof(*double));
        // for (int i = 0; i < lines; i++) {
        //     matrix[i] = malloc(columns * sizeof(double));
        // }

        double **matrix = new double*[lines];
        for (int i = 0; i < lines; i++) {
            matrix[i] = new double[columns];
        }

        // BlockMatrix bm(lines, columns, matrix);
        // *bm = BlockMatrix(lines, columns, matrix);

        BlockMatrix tmp(lines, columns, matrix);
        bm = &tmp;

        // bm = &block_mat(lines, columns, matrix);

        // while ( getc(matrix_file) != EOF) {
        int line;
        int prev_line, prev_column = 0;
        while (fscanf(matrix_file, "%d", &line) > 0) {
            // int line, column;
            int column;
            double value;
            // fscanf(matrix_file, "%d", &line);
            fscanf(matrix_file, "%d", &column);
            fscanf(matrix_file, "%lf", &value);
            //comvercao para a notacao de indices de 0 a N-1
            line--;
            column--;
            // printf("line: %d, column: %d, value: %lf\n", line, column, value);
            fill_previous(prev_line, prev_column, line, column, matrix, lines, columns);
            // TODO e se o valor do último elemento não for especificado?
            // não tratei esse tipo de coisa, melhor perguntar no PACA.
            prev_line = line;
            prev_column = column;
            matrix[line][column] = value;
        }

        // print_matrix(lines, columns, matrix);
        print_matrix(lines, columns, bm->matrix);


        fclose (matrix_file);
    } else cout << "Unable to open file\n";


    return *bm;
}

