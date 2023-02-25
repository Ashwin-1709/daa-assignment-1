#include "dcel.hh"
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

void enumerate_face(const Face &face) {
    Edge *start = face.edge;
    auto cur = start->next;
    std::vector<Vertex *> vertices;
    vertices.push_back(start->origin);
    while (cur != start) {
        vertices.push_back(cur->origin);
        cur = cur->next;
    }
    for (auto &u : vertices) {
        std::cout << u->p.x << " " << u->p.y << "\n";
    }
}

// The angle swept by a counterclockwise rotation from bc to ba
double angle(const Point &a, const Point &b, const Point &c) {
    auto mag_ba =
        std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    auto mag_bc =
        std::sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
    auto dot = (a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y);
    auto cos_theta = dot / (mag_ba * mag_bc);
    auto cross = (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
    auto sin_theta = cross / (mag_ba * mag_bc);
    if (sin_theta == 0) {
        if (cos_theta > 0) {
            return 0.0;
        } else {
            return 180.0;
        }
    } else if (sin_theta > 0) {
        return std::acos(cos_theta) * 180 / M_PI;
    } else {
        return 360.0 - (std::acos(cos_theta) * 180 / M_PI);
    }
}
