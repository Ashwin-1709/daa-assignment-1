#include "dcel.hh"
#include "dcel_fixture.hh"
#include "typedefs.hh"
#include "utils.hh"
#include <deque>
#include <gtest/gtest.h>
#include <vector>

TEST_F(DcelFixture, snake_1) {
    n_vertices_ = 12;
    points_ = std::deque<Point>{
        Point(10, 0),  Point(20, 10), Point(30, 0),  Point(40, 10),
        Point(50, 0),  Point(50, 10), Point(40, 20), Point(30, 10),
        Point(20, 20), Point(10, 10), Point(0, 20),  Point(0, 10),
    };
    polygon_ = Polygon(points_);
    add_edge(polygon_.vertices[1], polygon_.vertices[7]);
    add_edge(polygon_.vertices[7], polygon_.vertices[11]);
    polygons_ = std::set<Face *>();
    auto indices = std::vector<std::vector<usize>>(
        {{1, 7, 6, 5, 4, 3, 2}, {7, 11, 10, 9, 8}});
    check(2, indices);
}
