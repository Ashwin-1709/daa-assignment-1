#include "dcel.hh"
using namespace std;

// Debug Polygon
void dbg(DCEL *x) {
    Vertex *start = x->polygon[0];
    cout << "Starting at " << start->index << endl;
    Vertex *cur = start->incident_edge->next->origin;
    while (cur != start) {
        cout << "Currently at  " << cur->index
             << " Previous : " << cur->incident_edge->prev->origin->index
             << " Next Vertex: " << cur->incident_edge->next->origin->index
             << "\n";
        cout << "Twin Vertex at " << cur->incident_edge->twin->origin->index
             << "\n";
        cur = cur->incident_edge->next->origin;
    }
}

int main() {
    int n;
    cin >> n;
    deque<Point> points;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        Point p;
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    DCEL *polygon = new DCEL(points);
    dbg(polygon);
    Point a, b;
    a.x = 3.25, a.y = 1.4;
    b.x = 2.8, b.y = -2.3;

    auto x = get_line(a, b);
    cout << x[0] << ' ' << x[1] << ' ' << x[2] << '\n';
    Point c, d;
    c.x = 3.5, c.y = 2;
    d.x = 2.5, d.y = -5;
    cout << same_side_semiplane(x, c, d) << '\n';
    c.x = 3.3, c.y = 2;
    cout << same_side_semiplane(x, c, d) << '\n';
    d.x = 3, d.y = 2;
    cout << same_side_semiplane(x, c, d) << '\n';
}
