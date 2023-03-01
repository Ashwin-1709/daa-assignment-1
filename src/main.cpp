#include "dcel.hh"
#include "decomp.hh"
#include "utils.hh"

int main() {
    int n;
    std::cin >> n;
    std::deque<Point> points;
    for (int i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        Point p;
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    Polygon *polygon = new Polygon(points);
    auto p = decompose(polygon);
    std::set<Face*>faces = {polygon->open_end , polygon->inner_end};
    Enumerate_Polygons(faces);
}
