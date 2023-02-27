C++ = g++
CXXFLAGS = -Wextra -Wshadow -Wconversion -Wpedantic -Werror -Wno-c++98-compat -Wno-float-equal -g
default:
	$(C++) dcel.hh dcel.cc utils.hh utils.cc main.cpp $(CXXFLAGS)