#ifndef DCEL_H
#define DCEL_H
#include <bits/stdc++.h>

class Vertex;
class Edge;
class Face {
  public:
    Edge *edge;
};

class Edge {
  public:
    Vertex *origin;
    Edge *twin;
    Face *left_face;
    Edge *next;
    Edge *prev;
};

class Point {
  public:
    double x, y;
};

class Vertex {
  public:
    Point point;
    int index;
    Edge *incident_edge;
    Vertex(Point &pt, int &id) : point(pt), index(id) {}
};

class DCEL {
  public:
    std::deque<Vertex *> polygon;
    int n;
    DCEL(std::deque<Point> &point_list);

  private:
    std::deque<std::array<Edge *, 2>> EdgeList;
};

void enumerate_face(const Face &face);

double angle(const Point &a, const Point &b, const Point &c);
std::deque<Vertex *> get_notches(std::deque<Vertex *> polygon);
std::array<Point, 2> get_rectangle(std::deque<Vertex *> &L);
bool inside_rectangle(std::array<Point, 2> &rectangle, const Point &point);
std::array<double, 3> get_line(const Point &a, const Point &b);
bool same_side_semiplane(std::array<double, 3> &coef, const Point &a,
                         const Point &b);
void decompose(const DCEL &dcel);
Vertex *next_vertex(Vertex *v);
bool check_notch(Vertex *a, Vertex *b, Vertex *c, Vertex *start,
                 Vertex *second);
#endif // DCEL_H
