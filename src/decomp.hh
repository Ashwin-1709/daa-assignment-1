#ifndef DECOMP_H
#define DECOMP_H
#include "typedefs.hh"
#include "utils.hh"
#include <deque>

std::set<Face *> decompose(Polygon *polygon);
std::set<Face *> merge(Polygon *polygon);

#endif // DECOMP_H
