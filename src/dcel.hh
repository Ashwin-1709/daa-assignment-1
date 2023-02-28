#ifndef DCEL_H
#define DCEL_H
#include "typedefs.hh"
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
    Point() {}
    Point(double x_arg, double y_arg) : x(x_arg), y(y_arg) {}
};

class Vertex {
  public:
    Point point;
    usize index;
    Edge *incident_edge;
    Vertex(Point pt, usize id) : point(std::move(pt)), index(id) {}
};

class Polygon {
  public:
    Face *open_end;
    std::deque<Vertex *> vertices;
    usize n_vertices;
    Polygon(const std::deque<Point> &point_list);
    Polygon();

  private:
    std::deque<std::array<Edge *, 2>> EdgeList;
};

#endif
