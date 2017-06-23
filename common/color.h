#pragma once
#include "my_exception.h"

namespace Color {
	enum Color { Black, White, None };
	class NoSuchColorException: public Exception::Exception {
		using Exception::Exception;
	};

	std::string toString (Color color) noexcept;
	Color toColor (std::string color) throw (NoSuchColorException);
}