#ifndef UTILS_H
#define UTILS_H
#include "dcel.hh"
#include <set>

auto angle(const Point &a, const Point &b, const Point &c) -> double;
auto get_notches(const std::deque<Vertex *> &polygon) -> std::deque<Vertex *>;
auto get_LPVS(std::deque<Vertex *> &notches, std::deque<Vertex *> &L,
              std::deque<Vertex *> &P) -> std::deque<Vertex *>;
auto get_rectangle(const std::deque<Vertex *> &L) -> std::array<Point, 2>;
auto inside_rectangle(const std::array<Point, 2> &rectangle, const Point &point)
    -> bool;
auto get_line(const Point &a, const Point &b) -> std::array<double, 3>;
auto same_side_semiplane(const std::array<double, 3> &coef, const Point &a,
                         const Point &b) -> bool;
auto next_vertex(const Vertex *vertex) -> Vertex *;
auto next_vertex(Vertex *v, Face *f) -> Vertex *;
auto prev_vertex(Vertex *v, Face *f) -> Vertex *;
auto check_notch(const Vertex *a, const Vertex *b, const Vertex *c,
                 const Vertex *start, const Vertex *second) -> bool;
void update_face(Edge *edge, Face *face);
void enumerate_polygons(const std::set<Face *> &Polygons);
auto split_face(Vertex *v1, Vertex *v2, Face *cur) -> Face *;
auto is_collinear(const std::deque<Vertex *> &polygon) -> bool;
auto is_collinear(Face *f) -> bool;
auto is_inside_polygon(const std::deque<Vertex *> &polygon, Vertex *notch)
    -> bool;
auto merge_face(Face *f1, Face *f2) -> Face *;
auto is_convex(Vertex *v) -> bool;
#endif // UTILS_H
