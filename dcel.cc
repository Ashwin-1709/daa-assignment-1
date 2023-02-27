#include "dcel.hh"
#include "typedefs.hh"
#include <bits/stdc++.h>
using namespace std;

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

Polygon::Polygon(deque<Point> &point_list) {
    n_vertices = point_list.size();
    open_end = new Face();
    usize cur_id = 0;
    Vertex *start = new Vertex(point_list[0], cur_id);
    Edge *fwd = new Edge();
    Edge *rev = new Edge();
    fwd->twin = rev;
    rev->twin = fwd;
    start->incident_edge = fwd;
    fwd->origin = start;
    fwd->left_face = open_end;
    open_end->edge = fwd;
    vertices.push_back(start);
    for (usize i = 1; i < n_vertices; i++) {
        Vertex *cur = new Vertex(point_list[i], i);
        Edge *cur_fwd = new Edge();
        Edge *cur_rev = new Edge();
        cur_fwd->twin = cur_rev;
        cur_rev->twin = cur_fwd;
        cur->incident_edge = cur_fwd;
        cur_fwd->origin = cur;
        cur_fwd->left_face = open_end;

        vertices[i - 1]->incident_edge->next = cur_fwd;
        cur_fwd->prev = vertices[i - 1]->incident_edge;
        vertices[i - 1]->incident_edge->twin->prev = cur_rev;
        cur_rev->next = vertices[i - 1]->incident_edge->twin;

        vertices[i - 1]->incident_edge->twin->origin = cur;
        vertices.push_back(cur);
    }

    vertices[n_vertices - 1]->incident_edge->next = vertices[0]->incident_edge;
    vertices[0]->incident_edge->prev = vertices[n_vertices - 1]->incident_edge;
    vertices[n_vertices - 1]->incident_edge->twin->prev =
        vertices[0]->incident_edge->twin;
    vertices[0]->incident_edge->twin->next =
        vertices[n_vertices - 1]->incident_edge->twin;
    vertices[n_vertices - 1]->incident_edge->twin->origin = vertices[0];
}
