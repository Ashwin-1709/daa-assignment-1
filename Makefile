C++ = g++
CXXFLAGS = -g
default:
	$(C++) dcel.hh dcel.cc utils.hh utils.cc decomp.hh decomp.cc main.cpp $(CXXFLAGS)