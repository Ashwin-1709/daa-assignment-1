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

class Polygon {
  public:
    Face* open_end;
    std::deque<Vertex *> vertices;
    int n;
    Polygon(std::deque<Point> &point_list);

  private:
    std::deque<std::array<Edge *, 2>> EdgeList;
};

#endif
