#ifndef UTILS_H
#define UTILS_H
#include "dcel.hh"
#include <bits/stdc++.h>

// void enumerate_face(const Face &face);

double angle(const Point &a, const Point &b, const Point &c);
std::deque<Vertex *> get_notches(const std::deque<Vertex *> &polygon);
std::deque<Vertex *> get_LPVS(std::deque<Vertex *> &notches,
                              std::deque<Vertex *> &L, std::deque<Vertex *> &P);
std::array<Point, 2> get_rectangle(const std::deque<Vertex *> &L);
bool inside_rectangle(const std::array<Point, 2> &rectangle,
                      const Point &point);
std::array<double, 3> get_line(const Point &a, const Point &b);
bool same_side_semiplane(const std::array<double, 3> &coef, const Point &a,
                         const Point &b);
// void decompose(const DCEL &dcel);
Vertex *next_vertex(const Vertex *vertex);
bool check_notch(const Vertex *a, const Vertex *b, const Vertex *c,
                 const Vertex *start, const Vertex *second);
void add_edge(Vertex *v1, Vertex *vr);
void update_face(Edge *edge, Face *face);
#endif // UTILS_H
