#include "piece.h"

std::string toString (PieceType piece) NOEXCEPT {
	switch (piece) {
		case PieceType::Queen: return "Queen";
		case PieceType::Rook: return "Rook";
		case PieceType::Bishop: return "Bishop";
		case PieceType::Knight: return "Knight";
		case PieceType::Pawn: return "Pawn";
		case PieceType::King: return "King";
		case PieceType::None: return "None";
	}
}
PieceType toPiece (std::string piece) throw (NoSuchPieceException) {
	if (piece == "Queen")
		return PieceType::Queen;
	else if (piece == "Rook")
		return PieceType::Rook;
	else if (piece == "Bishop")
		return PieceType::Bishop;
	else if (piece == "Knight")
		return PieceType::Knight;
	else if (piece == "Pawn")
		return PieceType::Pawn;
	else if (piece == "King")
		return PieceType::King;
	else if (piece == "None")
		return PieceType::None;
	else
		throw NoSuchPieceException (piece);
}
