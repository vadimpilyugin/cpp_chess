#include "piece.h"

typedef Piece::PieceType PieceType;
typedef Piece::NoSuchPieceException NoSuchPieceException;

std::string Piece::toString (PieceType piece) noexcept {
	switch (piece) {
		case Queen: return "Queen";
		case Rook: return "Rook";
		case Bishop: return "Bishop";
		case Knight: return "Knight";
		case Pawn: return "Pawn";
		case King: return "King";
		case None: return "None";
	}
}
PieceType Piece::toPiece (std::string piece) throw (NoSuchPieceException) {
	if (piece == "Queen")
		return Queen;
	else if (piece == "Rook")
		return Rook;
	else if (piece == "Bishop")
		return Bishop;
	else if (piece == "Knight")
		return Knight;
	else if (piece == "Pawn")
		return Pawn;
	else if (piece == "King")
		return King;
	else if (piece == "None")
		return None;
	else
		throw NoSuchPieceException (piece);
}