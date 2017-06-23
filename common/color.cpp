#include "color.h"
using namespace Color;

std::string toString (Color::Color color) noexcept {
	switch (color) {
		case Black: return "Black";
		case White: return "White";
		case None: return "None";
	}
}
Color::Color toColor (std::string color) throw (NoSuchColorException) {
	if (color == "Black")
		return Black;
	else if (color == "White")
		return White;
	else if (color == "None")
		return None;
	else
		throw NoSuchColorException (color);
}