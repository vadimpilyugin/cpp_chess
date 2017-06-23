#pragma once

#include "chesscolor.h"
#include "tile.h"
#include "my_exception.h"

enum class PieceType {
	Queen,
	Rook,
	Bishop,
	Knight,
	Pawn,
	King,
	None
};

class NoSuchPieceException: Exception::Exception {
public:
    NoSuchPieceException(const std::string _msg): Exception(_msg) {}
};

struct Piece
{
    ChessColor color;
	PieceType type;
	bool hasMoved;
    Piece (): color (ChessColor::None), type (PieceType::None), hasMoved (false) {}
};

std::string toString (PieceType piece) NOEXCEPT;

PieceType toPiece (std::string piece) throw (NoSuchPieceException);

struct TiledPiece: public Piece {
	Tile place;
};
