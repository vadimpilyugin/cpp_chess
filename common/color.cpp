#include "color.h"

namespace Color {
	enum Color { Black, White };
	std::string toString (Color color) {
		switch (color) {
			case Black: {
				return "Black"
				break;
			}
			case White: {
				return "White";
				break;
			}
		}
	}
}

