#ifndef DECOMP_H
#define DECOMP_H
#include "typedefs.hh"
#include "utils.hh"
#include <deque>

std::deque<std::deque<Vertex *>> decompose(Polygon *polygon);

#endif // DECOMP_H
