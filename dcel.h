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

class Vertex {
  public:
    double x, y;
    Edge *incident_edge;
};

auto enumerate_face(Face *face) {
    Edge *start = face->edge;
    auto cur = start->next;
    std::vector<Vertex *> vertices;
    vertices.push_back(start->origin);
    while (cur != start) {
        vertices.push_back(cur->origin);
        cur = cur->next;
    }
    for (auto &u : vertices) {
        std::cout << u->x << " " << u->y << "\n";
    }
}
