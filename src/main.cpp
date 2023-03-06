#include "dbg.hh"
#include "dcel.hh"
#include "decomp.hh"
#include "utils.hh"
#include <cstdio>

auto main() -> int {
    usize n;
    std::cin >> n;
    std::cout << n << std::endl;
    std::deque<Point> points;
    for (usize i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        Point point;
        point.x = x;
        point.y = y;
        std::cout << x << " " << y << std::endl;
        points.push_back(point);
    }
    auto polygon = new Polygon(points);

    auto decompdata = decompose(*polygon);
    auto decomposed_polygons = merge(decompdata);
    enumerate_polygons(decomposed_polygons);
}
