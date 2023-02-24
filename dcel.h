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

class Vertex {
  public:
    double x, y;
    Edge *incident_edge;
};

void enumerate_face(Face *face);

double angle(Vertex *v1, Vertex *v2, Vertex *v3);

#endif // DCEL_H
