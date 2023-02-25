C++ = clang++
CXXFLAGS = -Weverything -Wextra -Wshadow -Wconversion -Wpedantic -Werror -Wno-c++98-compat -Wno-float-equal
default:
	$(C++) dcel.hh dcel.cc test.cpp $(CXXFLAGS)
