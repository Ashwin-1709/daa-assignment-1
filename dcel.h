#include <bits/stdc++.h>
#include <cmath>
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

auto angle(Vertex *v1 , Vertex *v2 , Vertex *v3) {
    std::vector<std::array<double , 2>>cord;
    for(auto v : {v1 , v2 , v3}) {
        cord.push_back({v->x , v->y });
    }
    auto dot = (cord[0][0] - cord[1][0]) * (cord[2][0] - cord[1][0]) + (cord[0][1] - cord[1][1]) * (cord[2][1] - cord[1][1]);
    auto mag_ba = std::sqrt((cord[0][0] - cord[1][0]) * (cord[0][0] - cord[1][0]) + (cord[0][1] - cord[1][1]) * (cord[0][1] - cord[1][1]));
    auto mag_bc = std::sqrt((cord[2][0] - cord[1][0]) * (cord[2][0] - cord[1][0]) + (cord[2][1] - cord[1][1]) * (cord[2][1] - cord[1][1]));
    auto cos_theta = dot / (mag_ba * mag_bc);
    return std::acos(cos_theta) * 180 / M_PI;
}
