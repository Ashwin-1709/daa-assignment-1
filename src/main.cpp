#include "dcel.hh"
#include "decomp.hh"
#include "utils.hh"
#include "dbg.hh"

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

    // Polygon *test = new Polygon({{30 , 10} , {40 , 20} , {50 , 10} , {50 ,
    // 0}}); Point *test_point = new Point({40 , 10}); Vertex *notch = new
    // Vertex(*test_point , 10); dbg(is_inside_polygon(test->vertices , notch));
    auto decomposed_polygons = merge(polygon);
    // std::set<Face*>p(begin(decomposed_polygons) , end(decomposed_polygons));
    // p.erase(decomposed_polygons[10]);
    // merge_face(decomposed_polygons[7] , decomposed_polygons[10]);
    std::cout << decomposed_polygons.size() << '\n';
    for(auto &f : decomposed_polygons)
        Enumerate_Face(f);
}
