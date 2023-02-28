#ifndef DCEL_FIXTURE_H
#define DCEL_FIXTURE_H
#include "dcel.hh"
#include "typedefs.hh"
#include "utils.hh"
#include <deque>
#include <gtest/gtest.h>
#include <vector>

class DcelFixture : public ::testing::Test {
  protected:
    usize n_vertices_;
    std::deque<Point> points_;
    std::set<Face *> polygons_;
    Polygon polygon_;
    void check(const usize &n, const std::vector<std::vector<usize>> &indices);
    // DcelFixture();
    // void SetUp();
    // DcelFixture(usize n, std::deque<Point> pts)
    //     : n_vertices_(n), points_(pts), polygon_(Polygon(pts)) {}
};

#endif // DCEL_FIXTURE_H
