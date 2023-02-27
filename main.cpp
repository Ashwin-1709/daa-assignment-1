#include "dcel.hh"
#include "utils.hh"
#include "decomp.hh"
using namespace std;

void Traverse(Polygon p) {
    set<Face*>polygons;
    Vertex *v = p.vertices[0];
    do {
        Edge *e = v->incident_edge;
        for(auto edges : {e , e->twin}) {
            if(edges->left_face != NULL and edges->left_face != p.open_end and edges->left_face->edge != NULL)
                polygons.insert(edges->left_face);
        }
        e = e->next;
        v = e->origin;
    } while(v != p.vertices[0]);

    cout << "Number of polygons : " << polygons.size() << '\n';
    for(auto y : polygons) {
        Edge *s = y->edge;
        vector<array<double , 2>>c;
        c.push_back({s->origin->point.x , s->origin->point.y});
        Edge *start = s->next;
        while(start->origin != s->origin) {
            c.push_back({start->origin->point.x , start->origin->point.y});
            start = start->next;
        }
        for(auto u : c) 
            cout << "(" << u[0] << "," << u[1] << ") ";
        cout << '\n';
    }
}

int main() {
    int n; cin >> n;
    deque<Point>points;
    for(int i = 0 ; i < n ; i++) {
        double x , y; cin >> x >> y;
        Point p;
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    Polygon *polygon = new Polygon(points);
    auto p = decompose(polygon);
    cout << p.size() << '\n';
    for(int i = 1 ; i < p.size() ; i++) {
        if(p[i].size() <= 2) continue;
        for(auto y : p[i])
            cout << "(" << y->point.x << "," << y->point.y << ") ";
        cout << '\n';
    }
}
