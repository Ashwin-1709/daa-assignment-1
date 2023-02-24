#include "dcel.h"
#include <cmath>
#include <vector>
#include <array>
#include <iostream>

void enumerate_face(Face *face) {
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

double angle(Vertex *v1, Vertex *v2, Vertex *v3) {
    std::vector<std::array<double, 2>> coords;
    for (auto v : {v1, v2, v3}) {
        coords.push_back({v->x, v->y});
    }
    auto dot = (coords[0][0] - coords[1][0]) * (coords[2][0] - coords[1][0]) +
               (coords[0][1] - coords[1][1]) * (coords[2][1] - coords[1][1]);
    auto mag_ba = std::sqrt(
        (coords[0][0] - coords[1][0]) * (coords[0][0] - coords[1][0]) +
        (coords[0][1] - coords[1][1]) * (coords[0][1] - coords[1][1]));
    auto mag_bc = std::sqrt(
        (coords[2][0] - coords[1][0]) * (coords[2][0] - coords[1][0]) +
        (coords[2][1] - coords[1][1]) * (coords[2][1] - coords[1][1]));
    auto cos_theta = dot / (mag_ba * mag_bc);
    return std::acos(cos_theta) * 180 / M_PI;
}
