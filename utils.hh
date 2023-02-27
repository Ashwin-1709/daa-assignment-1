#ifndef UTILS_H
#define UTILS_H
#include "dcel.hh"
#include <bits/stdc++.h>

// void enumerate_face(const Face &face);

double angle(const Point &a, const Point &b, const Point &c);
std::deque<Vertex *> get_notches(std::deque<Vertex *> polygon);
std::array<Point, 2> get_rectangle(std::deque<Vertex *> &L);
bool inside_rectangle(std::array<Point, 2> &rectangle, const Point &point);
std::array<double, 3> get_line(const Point &a, const Point &b);
bool same_side_semiplane(std::array<double, 3> &coef, const Point &a,
                         const Point &b);
// void decompose(const DCEL &dcel);
Vertex *next_vertex(Vertex *v);
bool check_notch(Vertex *a, Vertex *b, Vertex *c, Vertex *start,
                 Vertex *second);
void add_edge(Vertex *v1, Vertex *vr);
void update_face(Edge *e, Face *f);
#endif // UTILS_H
