#include "dcel.hh"
#include "utils.hh"
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
        cout << s->origin->index << ' ';
        Edge *start = s->next;
        while(start != s) {
            cout << start->origin->index << ' ';
            start = start->next;
        }
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
    add_edge(polygon->vertices[1] , polygon->vertices[7]);
    add_edge(polygon->vertices[0] , polygon->vertices[10]);
    Traverse(*polygon);
}
