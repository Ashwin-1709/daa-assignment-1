C++ = g++
CXXFLAGS = -Wextra -Wshadow -Wconversion -Wpedantic -Werror -Wno-float-equal -g
main:
	$(C++) dcel.cc utils.cc main.cpp $(CXXFLAGS)
test_dcel_construction:
	$(C++) dcel.cc utils.cc
test:
	$(C++) dcel.cc utils.cc
