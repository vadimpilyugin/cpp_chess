#pragma once

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#include <exception>
#include <string>

namespace Exception {
	class Exception: public std::exception {
		std::string msg;
	public:
		Exception(const std::string _msg): msg(_msg) {}
        virtual const char *what() const NOEXCEPT {
			return msg.c_str();
		}
	};
}
