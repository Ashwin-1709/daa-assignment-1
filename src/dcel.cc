/** \file */
#include "dcel.hh"
#include "typedefs.hh"

Polygon::Polygon() = default;

/// @brief Constructer for the Polygon class, Given a list of points in
/// clockwise order, It builds the DCEL structure for the polygon
/// @param point_list
Polygon::Polygon(const std::deque<Point> &point_list) {
    //
    n_vertices = point_list.size();
    open_end = new Face();
    inner_end = new Face();
    usize cur_id = 0;
    auto *start = new Vertex(point_list[0], cur_id);
    auto *forward = new Edge();
    auto *reverse = new Edge();

    forward->twin = reverse;
    reverse->twin = forward;
    start->incident_edge = forward;
    forward->origin = start;
    forward->left_face = open_end;
    open_end->edge = forward;
    inner_end->edge = reverse;
    vertices.push_back(start);

    for (usize i = 1; i < n_vertices; i++) {
        auto *current = new Vertex(point_list[i], i);
        auto *current_forward = new Edge();
        auto *current_reverse = new Edge();
        current_forward->twin = current_reverse;
        current_reverse->twin = current_forward;
        current->incident_edge = current_forward;
        current_forward->origin = current;
        current_forward->left_face = open_end;
        current_reverse->left_face = inner_end;

        vertices[i - 1]->incident_edge->next = current_forward;
        current_forward->prev = vertices[i - 1]->incident_edge;
        vertices[i - 1]->incident_edge->twin->prev = current_reverse;
        current_reverse->next = vertices[i - 1]->incident_edge->twin;

        vertices[i - 1]->incident_edge->twin->origin = current;
        vertices.push_back(current);
    }

    vertices[n_vertices - 1]->incident_edge->next = vertices[0]->incident_edge;
    vertices[0]->incident_edge->prev = vertices[n_vertices - 1]->incident_edge;
    vertices[n_vertices - 1]->incident_edge->twin->prev =
        vertices[0]->incident_edge->twin;
    vertices[0]->incident_edge->twin->next =
        vertices[n_vertices - 1]->incident_edge->twin;
    vertices[n_vertices - 1]->incident_edge->twin->origin = vertices[0];
}
