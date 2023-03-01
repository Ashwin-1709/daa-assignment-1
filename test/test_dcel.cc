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
    polygons_ = std::set<Face *>();
    auto indices = std::vector<std::vector<usize>>(
        {{1, 7, 6, 5, 4, 3, 2}, {7, 11, 10, 9, 8}});
    check(2, indices);
}

TEST_F(DcelFixture, comb_1) {
    n_vertices_ = 10;

    points_ = std::deque<Point>{
        Point(8, 0),  Point(7, 10), Point(6, 0),  Point(5, 10), Point(4, 0),
        Point(3, 10), Point(2, 0),  Point(1, 10), Point(0, 0),  Point(4, -2),
    };

    polygon_ = Polygon(points_);

    polygons_ = std::set<Face *>();
    auto indices = std::vector<std::vector<usize>>(
        {{9, 0, 1, 2, 3, 4}, {9, 4, 5, 6, 7, 8}});
    check(1, indices);
}
