#include "color.h"
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
	using Exception::Exception;
};
struct Piece
{
	Color color;
	PieceType type;
	bool hasMoved;
	Piece (): color (Color::None), type (PieceType::None), hasMoved (false) {}
};
std::string toString (PieceType piece) noexcept;
PieceType toPiece (std::string piece) throw (NoSuchPieceException);

struct TiledPiece: public Piece {
	Tile place;
};