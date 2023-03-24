#include "dcel.hh"
#include "decomp.hh"
#include "merge.hh"
#include "utils.hh"
#include <chrono>
#include <cstdio>
#include <iostream>

/// @brief Given list of points of input polygon in clockwise order, decomposes
/// it to convex polygons
auto main() -> int {
    usize n_vertices;
    std::cin >> n_vertices;
    std::cout << n_vertices << std::endl;
    std::deque<Point> points;
    for (usize i = 0; i < n_vertices; i++) {
        double x;
        double y;
        std::cin >> x >> y;
        Point point;
        point.x = x;
        point.y = y;
        std::cout << x << " " << y << std::endl;
        points.push_back(point);
    }
    auto *polygon = new Polygon(points);
    auto decompdata = decompose(*polygon);
    enumerate_polygons(decompdata.faces);
    auto decomposed_polygons = merge(decompdata);
    enumerate_polygons(decomposed_polygons);
}
