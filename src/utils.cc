/** \file */
#include "utils.hh"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

/// @brief Returns the angle swept by a counterclockwise rotation from line
/// segment ba to line segment bc
/// @param a The Vertex `a`
/// @param b The Vertex `b`
/// @param c The Vertex `c`
/// @return The angle abc
auto angle(const Point &a, const Point &b, const Point &c) -> double {
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
/// @brief Prints a set of polygons for visualization
/// @param Polygons The set of polygons
void enumerate_polygons(const std::set<Face *> &Polygons) {
    std::vector<std::deque<Vertex *>> polygons;
    for (const auto &face : Polygons) {
        std::deque<Vertex *> polygon;
        Edge *now = face->edge;
        do {
            polygon.push_back(now->origin);
            now = now->next;
        } while (now != face->edge);

        if (is_collinear(polygon)) {
            continue;
        }
        polygons.push_back(polygon);
    }

    std::cout << polygons.size() << '\n';

    for (auto &polygon : polygons) {
        std::cout << polygon.size() << '\n';
        for (auto &vertex : polygon) {
            std::cout << vertex->point.x << ' ' << vertex->point.y << ' ';
        }
        std::cout << '\n';
    }
}

/// @brief Get notches present in a polygon
/// @param polygon The polygon, as a deque of `Vertex`es
/// @return Deque of notches present in the polygon
auto get_notches(const std::deque<Vertex *> &polygon) -> std::deque<Vertex *> {
    std::deque<Vertex *> notches;
    const usize n_vertices = polygon.size();
    if (n_vertices < 3) {
        return notches;
    }
    for (usize i = 0; i < n_vertices; i++) {
        Vertex *base = polygon[i];
        Vertex *left = polygon[(i - 1 + n_vertices) % n_vertices];
        Vertex *right = polygon[(i + 1) % n_vertices];
        if (angle(left->point, base->point, right->point) > 180) {
            notches.push_back(base);
        }
    }
    return notches;
}

/// @brief Returns the extreme vertices of the vertical diagonal enclosing a
/// polygon
/// @param L The input polygon
/// @return Extreme vertices of the rectangle enclosing L
auto get_rectangle(const std::deque<Vertex *> &L) -> std::array<Point, 2> {
    Point minimum;
    Point maximum;
    minimum.x = 1e9, minimum.y = 1e9;
    maximum.x = -1e9, maximum.y = -1e9;
    for (const auto &vertex : L) {
        minimum.x = std::min(minimum.x, vertex->point.x);
        minimum.y = std::min(minimum.y, vertex->point.y);
        maximum.x = std::max(maximum.x, vertex->point.x);
        maximum.y = std::max(maximum.y, vertex->point.y);
    }
    return {minimum, maximum};
}
/// @brief Checks if a Point lies within a vertical rectangle represented by its
/// extreme vertices
/// @param rectangle The rectangle
/// @param point The Point
auto inside_rectangle(const std::array<Point, 2> &rectangle, const Point &point)
    -> bool {
    return point.x > rectangle[0].x and point.x < rectangle[1].x and
           point.y > rectangle[0].y and point.y < rectangle[1].y;
}
/// @brief 2D Equation of a line joining two `Point`s
/// @param a The first Point
/// @param b The second Point
/// @return Coefficients of the equation of the line: [a,b,c] in ax+by+c=0
auto get_line(const Point &a, const Point &b) -> std::array<double, 3> {
    // x1x + y1y + c = 0
    std::array<double, 3> coefficients;
    coefficients[0] = b.y - a.y;
    coefficients[1] = a.x - b.x;
    coefficients[2] = -(coefficients[0] * a.x + coefficients[1] * a.y);
    return coefficients;
}

/// @brief Checks if two Points are on the same side of a line
/// @param coef Coefficients of the equation of the line: [a,b,c] in ax+by+c=0
/// @param a The Point `a`
/// @param b The Point `b`
auto same_side_semiplane(const std::array<double, 3> &coef, const Point &a,
                         const Point &b) -> bool {
    double const line1 = coef[0] * a.x + coef[1] * a.y + coef[2];
    double const line2 = coef[0] * b.x + coef[1] * b.y + coef[2];
    return (line1 * line2) > 0;
}

/// @brief Returns the next Vertex in the original undecomposed polygon
/// @param vertex The Vertex whose next vertex is to be found
/// @return The next Vertex
auto next_vertex(const Vertex *vertex) -> Vertex * {
    return vertex->incident_edge->next->origin;
}

/// @brief Checks if any of the three angles a-b-c, b-c-start, and
/// c-start-second is a notch
/// @param a The Vertex `a`
/// @param b The Vertex `b`
/// @param c The Vertex `c`
/// @param start The Vertex `start`
/// @param second The Vertex `second`
auto check_notch(const Vertex *a, const Vertex *b, const Vertex *c,
                 const Vertex *start, const Vertex *second) -> bool {
    double const angle_b = angle(a->point, b->point, c->point);
    double const angle_c = angle(b->point, c->point, start->point);
    double const angle_start = angle(c->point, start->point, second->point);
    return angle_b <= 180 and angle_c <= 180 and angle_start <= 180;
}

/// @brief Splits a Face at the diagonal between two `Vertex`es
/// @param v1 The first Vertex
/// @param v2 The second Vertex
/// @param cur The Face
/// @return The new Face formed by splitting
auto split_face(Vertex *v1, Vertex *v2, Face *cur) -> Face * {
    Edge *e1;
    Edge *e2;
    Edge *now = cur->edge;
    do {
        if (now->origin == v1) {
            e1 = now;
        } else if (now->twin->origin == v2) {
            e2 = now;
        }
        now = now->next;
    } while (now != cur->edge);

    auto *e3 = new Edge();
    auto *e3_twin = new Edge();
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
    auto *new_face = new Face();
    update_face(e3_twin, new_face);
    return new_face;
}

/// @brief Merges two `Face`s into one face using the DCEL structure
/// @param f1 The first Face
/// @param f2 The second Face
/// @return The new Face formed by merging the two
auto merge_face(Face *face1, Face *face2) -> Face * {
    Edge *e3;
    Edge *now = face1->edge;
    do {
        if (now->left_face == face1 and now->twin->left_face == face2) {
            e3 = now;
        }
        now = now->next;
    } while (now != face1->edge);

    auto *e1 = e3->next;
    auto *e2 = e3->twin->next;
    e3->prev->next = e2;
    e2->prev = e3->prev;
    e1->prev = e3->twin->prev;
    e3->twin->prev->next = e1;
    face1->edge = e1;
    update_face(e1, face1);
    return face1;
}

/// @brief Sets the `Edge`s of the polygons' left Face to the given Face
/// @param edge An Edge of the polygon
/// @param face The Face `left_face` should point to
void update_face(Edge *edge, Face *face) {
    face->edge = edge;
    edge->left_face = face;
    auto *next = edge->next;
    while (next != edge) {
        next->left_face = face;
        next = next->next;
    }
    next->left_face = face;
}

/// @brief Returns the set of notches which are present in the polygon formed by
/// P \ L
/// @param notches The list of notches to match
/// @param L The polygon `L`
/// @param P The polygon `P`
/// @return List of notches in P \ L
auto get_LPVS(std::deque<Vertex *> &notches, std::deque<Vertex *> &L,
              std::deque<Vertex *> &P) -> std::deque<Vertex *> {
    std::deque<Vertex *> LPVS;
    for (auto *notch : notches) {
        if (std::find(L.begin(), L.end(), notch) == L.end() &&
            std::find(P.begin(), P.end(), notch) != P.end()) {
            LPVS.push_back(notch);
        }
    }
    return LPVS;
}

/// @brief Checks if all the `Vertex`es of a polygon are collinear
/// @param polygon The `Vertex`es of the polygon
auto is_collinear(const std::deque<Vertex *> &polygon) -> bool {
    const auto line = get_line(polygon[0]->point, polygon[1]->point);
    // line is ax + by + c = 0
    bool collinear = true;
    for (const auto &vertex : polygon) {
        auto &point = vertex->point;
        if (line[0] * point.x + line[1] * point.y + line[2] != 0) {
            collinear = false;
        }
    }
    return collinear;
}

/// @brief Checks if all the `Vertice`s of the polygon are collinear
/// @param f The Face representing the polygon
auto is_collinear(Face *face) -> bool {
    std::deque<Vertex *> polygon;
    Edge *now = face->edge;
    do {
        polygon.push_back(now->origin);
        now = now->next;
    } while (now != face->edge);
    return is_collinear(polygon);
}

/// @brief Checks if the angle made by a Vertex in the original polygon is
/// convex
/// @param v the Vertex v
auto is_convex(Vertex *vertex) -> bool {
    Vertex *nxt = vertex->incident_edge->next->origin;
    Vertex *pre = vertex->incident_edge->prev->origin;
    return angle(pre->point, vertex->point, nxt->point) <= 180;
}

/// @brief Checks whether a given notch lies inside the input polygon
/// @param polygon The polygon
/// @param notch The notch
auto is_inside_polygon(const std::deque<Vertex *> &polygon, Vertex *notch)
    -> bool {
    // Reference :
    // https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/PROJ2/InsidePoly.html
    usize const n_vertices = polygon.size();
    if (n_vertices < 3) {
        return false;
    }
    usize i;
    usize j;
    bool c = false;
    double const x = notch->point.x;
    double const y = notch->point.y;
    for (i = 0, j = n_vertices - 1; i < n_vertices; j = i++) {
        double const y1 = polygon[i]->point.y;
        double const x1 = polygon[i]->point.x;
        double const y2 = polygon[j]->point.y;
        double const x2 = polygon[j]->point.x;
        bool const in_between =
            (((y1 <= y) and (y < y2)) or ((y2 <= y) and (y < y1)));
        bool const interior = (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1);
        if (in_between and interior) {
            c = !c;
        }
    }
    return c;
}

/// @brief Returns the next Vertex of the edge of a Vertex in a Face
/// @param vertex The Vertex
/// @param face The Face
/// @return The next Vertex of v in Face f
auto next_vertex(Vertex *vertex, Face *face) -> Vertex * {
    Edge *now = face->edge;
    do {
        if (now->origin == vertex) {
            return now->next->origin;
        }
        now = now->next;
    } while (now != face->edge);
    assert(false);
    return now->origin;
}

/// @brief Returns the previous Vertex of the Edge of a Vertex in a Face
/// @param v The Vertex
/// @param f The Face
/// @return The previous Vertex of v in Face f
auto prev_vertex(Vertex *v, Face *f) -> Vertex * {
    Edge *now = f->edge;
    do {
        if (now->origin == v) {
            return now->prev->origin;
        }
        now = now->next;
    } while (now != f->edge);
    assert(false);
    return now->origin;
}
