#include "dcel.hh"
#include <bits/stdc++.h>

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

std::deque<Vertex *> get_notches(std::deque<Vertex *> &P) {
    std::deque<Vertex *> notches;
    int n = (int)P.size();
    if (n < 3)
        return notches;
    for (int i = 0; i < n; i++) {
        Vertex *base = P[i];
        Vertex *left = P[(i - 1 + n) % n];
        Vertex *right = P[(i + 1) % n];
        if (angle(left->p, base->p, right->p) > 180)
            notches.push_front(base);
    }
    return notches;
}

std::array<Point, 2> get_rectangle(std::deque<Vertex *> &L) {
    Point minimum, maximum;
    minimum.x = 1e9, minimum.y = 1e9;
    maximum.x = -1e9, maximum.y = -1e9;
    for (auto &v : L) {
        minimum.x = std::min(minimum.x, v->p.x);
        minimum.y = std::min(minimum.y, v->p.y);
        maximum.x = std::max(maximum.x, v->p.x);
        maximum.y = std::max(maximum.y, v->p.y);
    }
    return {minimum, maximum};
}

bool inside_rect(std::array<Point, 2> &rect, const Point &p) {
    if (p.x >= rect[0].x and p.x <= rect[1].x and p.y >= rect[0].y and
        p.y <= rect[1].y)
        return true;
    return false;
}

DCEL::DCEL(std::deque<Point>&Polygon) {
    Edge *front = NULL, *back = NULL;
    n = (int)Polygon.size();
    for (int i = 0; i < n; i++) {
        Vertex *v = new Vertex(Polygon[i], i);
        Edge *f = new Edge();
        Edge *b = new Edge();
        f->origin = v;
        f->twin = b;
        f->next = NULL;

        b->twin = f;
        b->next = back;
        b->origin = NULL;

        EdgeList.push_back({f, b});
        P.push_back(v);
        v->incident_edge = f;
        if (front)
            front->next = f;
        if (back)
            back->origin = v;
        front = f;
        back = b;
    }
    front->next = EdgeList[0][0];
    EdgeList[0][1]->next = back;
    back->origin = P[0];
    Vertex *prev = P.back();
    Vertex *cur = P[0];
    for (int i = 0; i < n; i++) {
        Edge *e = cur->incident_edge;
        Edge *f = prev->incident_edge;
        e->prev = f;
        prev = cur;
        cur = cur->incident_edge->next->origin;
    }
    prev = P[0];
    cur = P.back();
    for(int i = 0; i < n; i++) {
        Edge *e = prev->incident_edge->twin;
        Edge *f = cur->incident_edge->twin;
        e->next = f;
        prev = cur;
        cur = f->twin->origin;
    }
}