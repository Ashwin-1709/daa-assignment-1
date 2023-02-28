#include "dcel.hh"
#include "decomp.hh"
#include "utils.hh"

void Traverse(Polygon p) {
    std::set<Face *> polygons;
    Vertex *v = p.vertices[0];
    do {
        Edge *e = v->incident_edge;
        for (auto edges : {e, e->twin}) {
            if (edges->left_face != NULL and edges->left_face != p.open_end and
                edges->left_face->edge != NULL)
                polygons.insert(edges->left_face);
        }
        e = e->next;
        v = e->origin;
    } while (v != p.vertices[0]);

    std::cout << "Number of polygons : " << polygons.size() << '\n';
    for (auto y : polygons) {
        Edge *s = y->edge;
        std::vector<std::array<double, 2>> c;
        c.push_back({s->origin->point.x, s->origin->point.y});
        Edge *start = s->next;
        while (start->origin != s->origin) {
            std::cout << start->origin->index << ' ';
            start = start->next;
        }
        for (auto u : c)
            std::cout << "(" << u[0] << "," << u[1] << ") ";
        std::cout << '\n';
    }
}

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
    auto p = decompose(polygon);
    std::cout << p.size() << '\n';
    for (usize i = 1; i < p.size(); i++) {
        if (p[i].size() <= 2)
            continue;
        for (auto y : p[i])
            std::cout << "(" << y->point.x << "," << y->point.y << ") ";
        std::cout << '\n';
    }
}
