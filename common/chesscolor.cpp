#include "chesscolor.h"

std::string toString (ChessColor color) NOEXCEPT {
	switch (color) {
        case ChessColor::Black: return "Black";
        case ChessColor::White: return "White";
        case ChessColor::None: return "None";
	}
    return "None";
}

ChessColor toColor (std::string color) throw (NoSuchColorException) {
	if (color == "Black")
        return ChessColor::Black;
	else if (color == "White")
        return ChessColor::White;
	else if (color == "None")
        return ChessColor::None;
	else
        throw NoSuchColorException(color);
}
