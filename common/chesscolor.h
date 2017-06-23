#pragma once
#include "my_exception.h"

enum class ChessColor { Black, White, None };
class NoSuchColorException: public Exception::Exception {
public:
    NoSuchColorException(const std::string _msg): Exception(_msg) {}
};

std::string toString (ChessColor color) NOEXCEPT;
ChessColor toColor (std::string color) throw (NoSuchColorException);
