#include "color.h"

std::string toString (Color color) noexcept {
	switch (color) {
		case Color::Black: return "Black";
		case Color::White: return "White";
		case Color::None: return "None";
	}
}
Color toColor (std::string color) throw (NoSuchColorException) {
	if (color == "Black")
		return Color::Black;
	else if (color == "White")
		return Color::White;
	else if (color == "None")
		return Color::None;
	else
		throw NoSuchColorException (color);
}