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
        std::cout << u->point.x << " " << u->point.y << "\n";
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

std::deque<Vertex *> get_notches(std::deque<Vertex *> polygon) {
    std::deque<Vertex *> notches;
    int n = (int)polygon.size();
    if (n < 3)
        return notches;
    for (int i = 0; i < n; i++) {
        Vertex *base = polygon[i];
        Vertex *left = polygon[(i - 1 + n) % n];
        Vertex *right = polygon[(i + 1) % n];
        if (angle(left->point, base->point, right->point) > 180)
            notches.push_back(base);
    }
    return notches;
}

// rectangle with minimum area that encloses vertices of list L
std::array<Point, 2> get_rectangle(std::deque<Vertex *> &L) {
    Point minimum, maximum;
    minimum.x = 1e9, minimum.y = 1e9;
    maximum.x = -1e9, maximum.y = -1e9;
    for (auto &v : L) {
        minimum.x = std::min(minimum.x, v->point.x);
        minimum.y = std::min(minimum.y, v->point.y);
        maximum.x = std::max(maximum.x, v->point.x);
        maximum.y = std::max(maximum.y, v->point.y);
    }
    return {minimum, maximum};
}

bool inside_rectangle(std::array<Point, 2> &rectangle, const Point &point) {
    if (point.x >= rectangle[0].x and point.x <= rectangle[1].x and
        point.y >= rectangle[0].y and point.y <= rectangle[1].y)
        return true;
    return false;
}

DCEL::DCEL(std::deque<Point> &point_list) {
    Edge *front = NULL, *back = NULL;
    n = (int)point_list.size();
    for (int i = 0; i < n; i++) {
        Vertex *v = new Vertex(point_list[i], i);
        Edge *f = new Edge();
        Edge *b = new Edge();
        f->origin = v;
        f->twin = b;
        f->next = NULL;

        b->twin = f;
        b->next = back;
        b->origin = NULL;

        EdgeList.push_back({f, b});
        polygon.push_back(v);
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
    back->origin = polygon[0];
    Vertex *prev = polygon.back();
    Vertex *cur = polygon[0];
    for (int i = 0; i < n; i++) {
        Edge *e = cur->incident_edge;
        Edge *f = prev->incident_edge;
        e->prev = f;
        prev = cur;
        cur = cur->incident_edge->next->origin;
    }
    prev = polygon[0];
    cur = polygon.back();
    for (int i = 0; i < n; i++) {
        Edge *e = prev->incident_edge->twin;
        Edge *f = cur->incident_edge->twin;
        e->next = f;
        prev = cur;
        cur = f->twin->origin;
    }
}

std::array<double, 3> get_line(const Point &a, const Point &b) {
    // x1x + y1y + c = 0
    std::array<double, 3> coefficients;
    coefficients[0] = b.y - a.y;
    coefficients[1] = a.x - b.x;
    coefficients[2] = -(coefficients[0] * a.x + coefficients[1] * a.y);
    return coefficients;
}

bool same_side_semiplane(std::array<double, 3> &coef, const Point &a,
                         const Point &b) {
    double L1 = coef[0] * a.x + coef[1] * a.y + coef[2];
    double L2 = coef[0] * b.x + coef[1] * b.y + coef[2];
    if ((L1 * L2) > 0)
        return true;
    return false;
}

Vertex *next_vertex(Vertex *v) {
    Edge *nxt_edge = v->incident_edge->next;
    return nxt_edge->origin;
}

bool check_notch(Vertex *a, Vertex *b, Vertex *c, Vertex *start,
                 Vertex *second) {
    double angle_b = angle(a->point, b->point, c->point);
    double angle_c = angle(b->point, c->point, start->point);
    double angle_start = angle(c->point, start->point, second->point);
    return angle_b <= 180 and angle_c <= 180 and angle_start <= 180;
}

void decompose(const DCEL &dcel) {
    int n = dcel.n;
    // std::deque<std::deque<Vertex *>> L;
    // std::deque<Vertex *> cur, notches = get_notches(dcel.polygon);
    // cur.push_front(dcel.polygon[0]);
    // L.push_front(cur);
    // int m = 1;
    // while (n > 3) {
    //     Vertex *v1 = L[m - 1].back();
    //     Vertex *v2 = next_vertex(v1);
    //     cur.clear();
    //     cur.push_back(v1);
    //     cur.push_back(v2);

    //     Vertex *pre = v1;
    //     Vertex *now = v2;
    //     Vertex *nxt = next_vertex(v2);
    //     while (check_notch(pre, now, nxt, v1, v2)) {
    //         cur.push_back(nxt);
    //         pre = now;
    //         now = nxt;
    //         nxt = next_vertex(nxt);
    //     }

    //     if ((int)cur.size() != n) {
            
    //     }
    // }
}
