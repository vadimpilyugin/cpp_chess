#include "piece.h"


struct Piece
{
	Color type;
	PieceType type;
	bool hasMoved;
};

struct TiledPiece: public Piece {
	Tile place;
};
