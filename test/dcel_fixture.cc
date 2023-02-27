#include "dcel_fixture.hh"
#include "dcel.hh"
#include "typedefs.hh"
#include "utils.hh"
#include <deque>
#include <gtest/gtest.h>
#include <vector>

void DcelFixture::check(usize exp_polygons,
                        std::vector<std::vector<usize>> exp_indices) {
    Vertex *vertex = polygon_.vertices[0];

    do {
        Edge *edge = vertex->incident_edge;
        for (auto edges : {edge, edge->twin}) {
            if (edges->left_face != NULL and
                edges->left_face != polygon_.open_end and
                edges->left_face->edge != NULL)
                polygons_.insert(edges->left_face);
        }
        edge = edge->next;
        vertex = edge->origin;
    } while (vertex != polygon_.vertices[0]);

    EXPECT_EQ(exp_polygons, polygons_.size());

    auto indices_vec = std::vector<std::vector<usize>>();

    for (auto p : polygons_) {
        auto indices = std::vector<usize>();
        Edge *s = p->edge;
        indices.push_back(s->origin->index);

        Edge *start = s->next;
        while (start->origin != s->origin) {
            indices.push_back(start->origin->index);
            start = start->next;
        }
    }
    for (usize i = 0; i < indices_vec.size(); i++) {
        auto indices = indices_vec.at(i);
        for (usize j = 0; j < indices.size(); j++) {
            EXPECT_EQ(indices[j], exp_indices[i][j]);
        }
    }
}
