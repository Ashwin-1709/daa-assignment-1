#include "utils.hh"
#include "bits/stdc++.h"

// The angle swept by a counterclockwise rotation from bc to ba
double angle(const Point &a, const Point &b, const Point &c) {
    auto mag_ba =
        std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    auto mag_bc =
        std::sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
    auto dot = (a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y);
    auto cos_theta = min(1.0 , dot / (mag_ba * mag_bc));
    cos_theta = max(cos_theta , -1.0);
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
    usize n = polygon.size();
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
    // dbg(a->point.x , a->point.y , b->point.x , b->point.y , c->point.x , c->point.y);
    // dbg(start->point.x , start->point.y , second->point.x , second->point.y);
    double angle_b = angle(a->point, b->point, c->point);
    double angle_c = angle(b->point, c->point, start->point);
    double angle_start = angle(c->point, start->point, second->point);
    // dbg(angle_b , angle_c , angle_start);
    return angle_b <= 180 and angle_c <= 180 and angle_start <= 180;
}

void update_face(Edge *e , Face *f) {
    e->left_face = f;
    Edge *nxt = e->next;
    while(nxt != e) {
        nxt->left_face = f;
        nxt = nxt->next;
    }
}

void add_edge(Vertex *v1, Vertex *vr) {
    //edge from v1 to vr updating everything
    Edge *from_v1 = v1->incident_edge;
    Edge *from_vr = vr->incident_edge;

    Edge *back_v1 = from_v1->prev;
    Edge *back_vr = from_vr->prev;
 
    Edge *v1_vr = new Edge();
    Edge *vr_v1 = new Edge();
    // Half Edge from v1 to vr
    v1_vr->twin = vr_v1;
    vr_v1->twin = v1_vr;
    v1_vr->origin = v1;
    vr_v1->origin = vr;

    //next of old edges to joint edges
    from_vr = from_vr->twin;
    from_vr->next = vr_v1;
    vr_v1->prev = from_vr;

    from_v1 = from_v1->twin;
    from_v1->next = v1_vr;
    v1_vr->prev = from_v1;
    //next of new edges to corresponding edges

    back_v1 = back_v1->twin;
    back_v1->prev = vr_v1;
    vr_v1->next = back_v1;

    back_vr = back_vr->twin;
    back_vr->prev = v1_vr;
    v1_vr->next = back_vr;

    Face *polygon = new Face();
    polygon->edge = v1_vr;
    update_face(v1_vr , polygon);
}

deque<Vertex*> get_LPVS(deque<Vertex*> &notches , deque<Vertex*> &L , deque<Vertex*> &P) {
    deque<Vertex*> LPVS;
    for(auto notch : notches) {
        bool in_P = false , in_L = false;
        for(auto cur : L) 
            in_L |= (cur == notch);
        for(auto cur : P)
            in_P |= (cur == notch);
        if(in_P and !in_L)
            LPVS.push_back(notch);
    }
    return LPVS;
}