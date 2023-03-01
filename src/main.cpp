#include "dcel.hh"
#include "decomp.hh"
#include "utils.hh"

int main() {
    usize n;
    std::cin >> n;
    std::deque<Point> points;
    for (usize i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        Point p;
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    Polygon *polygon = new Polygon(points);
    
    auto decomposed_polygons = decompose(polygon);
    Enumerate_Polygons(decomposed_polygons);
}
