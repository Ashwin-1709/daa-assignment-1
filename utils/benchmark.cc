#include "dcel.hh"
#include "decomp.hh"
#include "merge.hh"
#include "utils.hh"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>

using namespace std::chrono;

template <typename T> auto std_deviation(std::vector<T> numbers, T mean) -> T {
    u128 accumulator = 0;
    for (auto number : numbers) {
        auto diff = std::max(number, mean) - std::min(number, mean);
        accumulator += diff * diff;
    }
    return (T)std::sqrt(accumulator / numbers.size());
}

auto count_polygons(const std::set<Face *> &Polygons) -> usize {
    usize polygons = 0;
    for (const auto &f : Polygons) {
        std::deque<Vertex *> p;
        Edge *now = f->edge;
        do {
            p.push_back(now->origin);
            now = now->next;
        } while (now != f->edge);

        if (is_collinear(p)) {
            continue;
        }
        polygons++;
    }
    return polygons;
}

auto main() -> int {
    std::ofstream os("output.csv");
    os << "Name, No. of vertices, Time to decompose, Time to merge, Number of "
          "polygons before merging, Number of polygons after merging"
       << std::endl;
    usize cases;
    std::cin >> cases;
    while (cases--) {
        std::string name;
        std::cin >> name;
        os << name << ",";
        usize n_vertices;
        std::cin >> n_vertices;
        os << n_vertices << ",";
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
        auto decomp_times = std::vector<u128>();
        for (usize i = 0; i < 50; i++) {
            auto *polygon = new Polygon(points);
            auto start = high_resolution_clock::now();
            auto decompdata = decompose(*polygon); //
            auto end = high_resolution_clock::now();
            decomp_times.push_back(
                (u128)duration_cast<microseconds>(end - start).count());
        }
        auto decomp_mean =
            std::accumulate(decomp_times.begin(), decomp_times.end(), (u128)0) /
            decomp_times.size();
        auto decomp_deviation = std_deviation(decomp_times, decomp_mean);
        os << (u64)decomp_mean << "±" << (u64)decomp_deviation << ",";
        auto *polygon = new Polygon(points);
        auto decompdata = decompose(*polygon); //
        auto before_merge_polygons = count_polygons(decompdata.faces);
        auto merge_times = std::vector<u128>();
        for (usize i = 0; i < 50; i++) {
            auto *polygon2 = new Polygon(points);
            auto decompdata2 = decompose(*polygon2); //
            auto start = high_resolution_clock::now();
            auto decomposed_polygons = merge(decompdata2); //
            auto end = high_resolution_clock::now();
            merge_times.push_back(
                (u128)duration_cast<microseconds>(end - start).count());
        }
        auto merge_mean =
            std::accumulate(merge_times.begin(), merge_times.end(), (u128)0) /
            merge_times.size();
        auto merge_deviation = std_deviation(decomp_times, decomp_mean);
        os << (u64)merge_mean << "±" << (u64)merge_deviation << ",";
        auto after_merge_polygons = count_polygons(merge(decompdata)); //
        os << before_merge_polygons << "," << after_merge_polygons << std::endl;
    }
}
