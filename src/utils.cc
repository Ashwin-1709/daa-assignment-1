#include "utils.hh"
#include <algorithm>
#include <bits/stdc++.h>
#include <dbg.hh>

// The angle swept by a counterclockwise rotation from bc to ba
double angle(const Point &a, const Point &b, const Point &c) {
    const auto mag_ba =
        std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    const auto mag_bc =
        std::sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
    const auto dot = (a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y);
    const auto cos_theta = std::clamp(dot / (mag_ba * mag_bc), -1.0, 1.0);
    const auto cross = (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
    if (cross == 0) {
        if (cos_theta > 0) {
            return 0.0;
        } else {
            return 180.0;
        }
    } else if (cross > 0) {
        return std::acos(cos_theta) * 180 / M_PI;
    } else {
        return 360.0 - (std::acos(cos_theta) * 180 / M_PI);
    }
}

void Enumerate_Polygons(std::set<Face *> Polygons) {
    usize cnt = 1;
    std::vector<std::deque<Vertex*>>polygons;
    for (auto &f : Polygons) {
        std::deque<Vertex*>p;
        Edge *now = f->edge;
        do {
            p.push_back(now->origin);
            now = now->next;
        } while (now != f->edge);
        
        if(is_collinear(p)) continue;
        polygons.push_back(p);
    }
    std::cout << polygons.size() << '\n';
    for(auto &vt : polygons) {
        for(auto &u : vt) {
            std::cout << u->point.x << ' ' << u->point.y << ' ';
        }
        std::cout << '\n';
    }
}

std::deque<Vertex *> get_notches(const std::deque<Vertex *> &polygon) {
    std::deque<Vertex *> notches;
    const usize n = polygon.size();
    if (n < 3)
        return notches;
    for (usize i = 0; i < n; i++) {
        Vertex *base = polygon[i];
        Vertex *left = polygon[(i - 1 + n) % n];
        Vertex *right = polygon[(i + 1) % n];
        if (angle(left->point, base->point, right->point) > 180)
            notches.push_back(base);
    }
    return notches;
}

// rectangle with minimum area that encloses vertices of list L
std::array<Point, 2> get_rectangle(const std::deque<Vertex *> &L) {
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

bool inside_rectangle(const std::array<Point, 2> &rectangle,
                      const Point &point) {
    if (point.x > rectangle[0].x and point.x < rectangle[1].x and
        point.y > rectangle[0].y and point.y < rectangle[1].y)
        return true;
    return false;
}

std::array<double, 3> get_line(const Point &a, const Point &b) {
    // x1x + y1y + c = 0
    std::array<double, 3> coefficients;
    coefficients[0] = b.y - a.y;
    coefficients[1] = a.x - b.x;
    coefficients[2] = -(coefficients[0] * a.x + coefficients[1] * a.y);
    return coefficients;
}

bool same_side_semiplane(const std::array<double, 3> &coef, const Point &a,
                         const Point &b) {
    double L1 = coef[0] * a.x + coef[1] * a.y + coef[2];
    double L2 = coef[0] * b.x + coef[1] * b.y + coef[2];
    if ((L1 * L2) > 0)
        return true;
    return false;
}

Vertex *next_vertex(const Vertex *vertex) {
    return vertex->incident_edge->next->origin;
}

bool check_notch(const Vertex *a, const Vertex *b, const Vertex *c,
                 const Vertex *start, const Vertex *second) {
    double angle_b = angle(a->point, b->point, c->point);
    double angle_c = angle(b->point, c->point, start->point);
    double angle_start = angle(c->point, start->point, second->point);
    return angle_b <= 180 and angle_c <= 180 and angle_start <= 180;
}

Face *split_face(Vertex *v1, Vertex *v2, Face *cur) {

    Edge *e1, *e2;
    Edge *now = cur->edge;
    do {
        if (now->origin == v1)
            e1 = now;
        else if (now->twin->origin == v2)
            e2 = now;
        now = now->next;
    } while (now != cur->edge);

    Edge *e3 = new Edge();
    Edge *e3_twin = new Edge();
    e3->twin = e3_twin;
    e3_twin->twin = e3;
    e3->origin = v1;
    e3_twin->origin = v2;

    e1->prev->next = e3;
    e3->prev = e1->prev;
    e3->next = e2->next;
    e2->next->prev = e3;
    e3->left_face = cur;
    update_face(e3, cur);

    e3_twin->next = e1;
    e1->prev = e3_twin;
    e2->next = e3_twin;
    e3_twin->prev = e2;
    Face *new_face = new Face();
    update_face(e3_twin, new_face);
    return new_face;
}

void update_face(Edge *edge, Face *face) {
    face->edge = edge;
    edge->left_face = face;
    Edge *next = edge->next;
    while (next != edge) {
        next->left_face = face;
        next = next->next;
    }
    next->left_face = face;
}

std::deque<Vertex *> get_LPVS(std::deque<Vertex *> &notches,
                              std::deque<Vertex *> &L,
                              std::deque<Vertex *> &P) {
    std::deque<Vertex *> LPVS;
    for (auto notch : notches) {
        bool in_P = false, in_L = false;
        for (auto cur : L)
            in_L |= (cur == notch);
        for (auto cur : P)
            in_P |= (cur == notch);
        if (in_P and !in_L)
            LPVS.push_back(notch);
    }
    return LPVS;
}

bool is_collinear(const std::deque<Vertex *> &polygon) {
    const auto line = get_line(polygon[0]->point, polygon[1]->point);
    // line is ax + by + c = 0
    bool collinear = true;
    for (auto &vertex : polygon) {
        auto &point = vertex->point;
        if (line[0] * point.x + line[1] * point.y + line[2] != 0) {
            collinear = false;
        }
    }
    return collinear;
}

bool is_inside_polygon(const std::deque<Vertex *> &polygon, Vertex *notch) {
    // Reference :
    // https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/PROJ2/InsidePoly.html
    usize n = polygon.size();
    if (n < 3)
        return false;
    usize i, j, c = 0;
    double x = notch->point.x, y = notch->point.y;
    for (i = 0, j = n - 1; i < n; j = i++) {
        double ypi = polygon[i]->point.y;
        double xpi = polygon[i]->point.x;
        double ypj = polygon[j]->point.y;
        double xpj = polygon[j]->point.x;
        if ((((ypi <= y) && (y < ypj)) || ((ypj <= y) && (y < ypi))) &&
            (x < (xpj - xpi) * (y - ypi) / (ypj - ypi) + xpi))
            c = !c;
    }
    return c;
}
