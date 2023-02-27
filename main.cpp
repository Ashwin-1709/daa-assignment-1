#include "dcel.hh"
using namespace std;

void Traverse(Polygon p) {
    Vertex *start = p.vertices[0];
    // cycle using next
    cout << "Starting at " << start->index << '\n';
    start = start->incident_edge->next->origin;
    while(start != p.vertices[0]) {
        cout << start->index << '\n';
        cout << "Face ? " << (start->incident_edge->left_face == p.open_end) << '\n';
        start = start->incident_edge->next->origin;
    }
    // cycle using prev
    start = p.vertices[0];
    cout << "Starting at " << start->index << '\n';
    start = start->incident_edge->prev->origin;
    while(start != p.vertices[0]) {
        cout << start->index << '\n';
        cout << "Face ? " << (start->incident_edge->left_face == p.open_end) << '\n';
        start = start->incident_edge->prev->origin;
    }
    // cycle using twin next
    Edge *ss = p.vertices[0]->incident_edge->twin;
    start = ss->origin;
    cout << "Starting at " << start->index << '\n';
    ss = ss->next;
    while(ss->origin != start) {
        cout << ss->origin->index << '\n';
        cout << "Face ? " << (ss->left_face == p.open_end) << '\n';
        ss = ss->next;
    }
    // cycle using twin prev
    Edge *s = p.vertices[0]->incident_edge->twin;
    start = s->origin;
    cout << "Starting at " << start->index << '\n';
    s = s->prev;
    while(s->origin != start) {
        cout << s->origin->index << '\n';
        cout << "Face ? " << (s->left_face == p.open_end) << '\n';
        s = s->prev;
    }
}

int main() {
    deque<Point> points = {{2 , -2} , {-2 , -4} , {-4 , 0} , {-2 , 1} , {0 , 2} , {2 , 0}};
    Polygon *polygon = new Polygon(points);
}
