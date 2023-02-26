C++ = g++
CXXFLAGS = -Wextra -Wshadow -Wconversion -Wpedantic -Werror -Wno-c++98-compat -Wno-float-equal
default:
	$(C++) dcel.hh dcel.cc main.cpp $(CXXFLAGS)