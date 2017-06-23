#include "basic.h"
#include <vector>
#define SIZE 8
#define TOTALPIECES 32


struct Tile_content: Tile{
	int piecenum;
	PieceType type;
	bool seenByWhite;
	bool seenByBlack;
	Tile_content(){
		type=None;
		seenByBlack=false;
		seenByWhite=false;
	}
};

struct Piece_dark: Piece{
	std::vector<Tile> vision;
};
	


