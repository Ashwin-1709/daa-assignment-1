#ifndef DCEL_H
#define DCEL_H
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
    Point p;
    Edge *incident_edge;
};

void enumerate_face(Face *face);

double angle(Point &a, Point &b, Point &c);

#endif // DCEL_H
