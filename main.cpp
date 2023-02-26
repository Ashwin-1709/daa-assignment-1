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
}
