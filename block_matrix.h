#ifndef BLOCK_MATRIX
#define BLOCK_MATRIX


class BlockMatrix {
public:
	int n_lines;
	int n_columns;
    double **matrix;
    /**************************************************************************/
    BlockMatrix (int _n_lines, int _n_columns, double **_matrix); // Construtor
    // int get_n_lines ();
    // int get_n_columns ();
    // void set_val (int line, int column, double val);
    // double get_val (int line, int column);
    void destroy ();
};

#endif
