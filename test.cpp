#include "dcel.h"

int main() {
    Vertex v1, v2, v3;
    v1.incident_edge = nullptr;
    v1.x = 0.0;
    v1.y = 0.0;

    v2.x = 0.0;
    v2.y = 1.0;

    v3.x = 1.0;
    v3.y = 1.0;
    Edge e1, e2, e3, e4, e5, e6;
    e1.origin = &v1;
    e1.twin = &e2;
    e2.origin = &v2;
    e2.twin = &e1;
    e1.next = &e3;


    e3.origin = &v2;
    e3.twin = &e4;
    e4.origin = &v3;
    e4.twin = &e3;
    e3.next = &e5;


    e5.origin = &v3;
    e5.twin = &e6;
    e6.origin = &v1;
    e6.twin = &e5;
    e5.next = &e1;

    v1.incident_edge = &e1;
    v2.incident_edge = &e3;
    v3.incident_edge = &e5;
    Face f;
    f.edge = &e1;
    enumerate_face(&f);
    std::cout << angle(&v1 , &v2 , &v3) << '\n';
}
