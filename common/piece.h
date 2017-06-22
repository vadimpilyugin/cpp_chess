#include "color.h"
#include "tile.h"


enum PieceType {
	Queen,
	Rook,
	Bishop,
	Knight,
	Pawn,
	King,
	None
}

struct Piece
{
	Color type;
	PieceType type;
	bool hasMoved;
};

struct TiledPiece: public Piece {
	Tile place;
};