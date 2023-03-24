#include "dcel.hh"
#include "decomp.hh"
#include "merge.hh"
#include "utils.hh"
#include <chrono>
#include <cstdio>
#include <bits/stdc++.h>

/// @brief Given list of points of input polygon in clockwise order, decomposes
/// it to convex polygons
auto main() -> int {
    usize n;
    std::cin >> n;
    std::cout << n << std::endl;
    std::deque<Point> points;
    for (usize i = 0; i < n; i++) {
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
