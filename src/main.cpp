#include "dbg.hh"
#include "dcel.hh"
#include "decomp.hh"
#include "merge.hh"
#include "utils.hh"
#include <cstdio>
#include <chrono>
using namespace std::chrono;

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
    auto start_decomp = high_resolution_clock::now();
    auto decompdata = decompose(*polygon);
    auto finish_decomp = high_resolution_clock::now();
    auto decomp_time = duration_cast<microseconds>(finish_decomp - start_decomp);
    std::cerr << "Time for decomposition algorith: " << decomp_time.count() << '\n';
    enumerate_polygons(decompdata.faces);
    auto merge_start = high_resolution_clock::now();
    auto decomposed_polygons = merge(decompdata);
    auto merge_end = high_resolution_clock::now();
    auto merge_time = duration_cast<microseconds>(merge_end - merge_start);
    std::cerr << "Time for merging: " << merge_time.count() << '\n';
    enumerate_polygons(decomposed_polygons);
}
