#ifndef BLOCK_MATRIX
#define BLOCK_MATRIX

class BlockMatrix;

class BlockMatrix {
public:
	int lines;
	int columns;

    // Lake *lake; // Lagoa
    // int id;     // ID do sapo
    // int gender; // Genero (Ra:0, Sapo:1)
    // int pos;    // Posicao do sapo na lagoa
    // /**************************************************************************/
    // BlockMatrix (int _lines, int _columns); // Construtor
    // void set_val (Lake *_lake);           // Define a lagoa
    // int can_move ();                       // Devolve a distancia que pode pular
    // void move (int dist);                  // Move o sapo dist pedras
};

#endif
