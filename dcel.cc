#include "dcel.hh"
#include <bits/stdc++.h>
using namespace std;

void enumerate_face(const Face &face) {
    Edge *start = face.edge;
    auto cur = start->next;
    std::vector<Vertex *> vertices;
    vertices.push_back(start->origin);
    while (cur != start) {
        vertices.push_back(cur->origin);
        cur = cur->next;
    }
    for (auto &u : vertices) {
        std::cout << u->point.x << " " << u->point.y << "\n";
    }
}


Polygon::Polygon(deque<Point>&point_list) {
    n = (int)point_list.size();
    open_end = new Face();
    int cur_id = 0;
    Vertex *start = new Vertex(point_list[0] , cur_id);
    Edge *fwd = new Edge();
    Edge *rev = new Edge();
    fwd->twin = rev;
    rev->twin = fwd;
    start->incident_edge = fwd;
    fwd->origin = start;
    fwd->left_face = open_end;
    open_end->edge = fwd;
    vertices.push_back(start);
    for(int i = 1 ; i < n ; i++) {
        Vertex *cur = new Vertex(point_list[i] , i);
        Edge* cur_fwd = new Edge();
        Edge *cur_rev = new Edge();
        cur_fwd->twin = cur_rev;
        cur_rev->twin = cur_fwd;
        cur->incident_edge = cur_fwd;
        cur_fwd->origin = cur;
        cur_fwd->left_face = open_end;

        vertices[i - 1]->incident_edge->next = cur_fwd;
        cur_fwd->prev = vertices[i - 1]->incident_edge;
        vertices[i - 1]->incident_edge->twin->prev = cur_rev;
        cur_rev->next = vertices[i - 1]->incident_edge->twin;

        vertices[i - 1]->incident_edge->twin->origin = cur;
        vertices.push_back(cur);
    }

    vertices[n - 1]->incident_edge->next = vertices[0]->incident_edge;
    vertices[0]->incident_edge->prev = vertices[n - 1]->incident_edge;
    vertices[n - 1]->incident_edge->twin->prev = vertices[0]->incident_edge->twin;
    vertices[0]->incident_edge->twin->next = vertices[n - 1]->incident_edge->twin;
    vertices[n - 1]->incident_edge->twin->origin = vertices[0];
}


// void add_edge(Vertex *v1 , Vertex *vr) {
//     //edge from v1 to vr updating everything
//     Edge *from_v1 = v1->incident_edge;
//     Edge *from_vr = vr->incident_edge;
//     std::cout << "v1 : " << from_v1->origin->index << '\n';
//     std::cout << "vr : " << from_vr->origin->index << '\n';
//     Edge *back_v1 = from_v1->prev;
//     Edge *back_vr = from_vr->prev;
//     std::cout << "back v1 : " << back_v1->origin->index << '\n';
//     std::cout << "back vr : " << back_vr->origin->index << '\n';
//     std::cout << "back twin v1 : " << back_v1->twin->origin->index << '\n';
//     std::cout << "back twin vr : " << back_vr->twin->origin->index << '\n';
//     std::cout << "back twin v1 : " << back_v1->twin->next->origin->index << '\n';
//     std::cout << "back twin vr : " << back_vr->twin->next->origin->index << '\n';
//     Edge *v1_vr = new Edge();
//     Edge *vr_v1 = new Edge();
//     // Half Edge from v1 to vr
//     v1_vr->twin = vr_v1;
//     vr_v1->twin = v1_vr;
//     v1_vr->origin = v1;
//     vr_v1->origin = vr;

//     //next of old edges to joint edges
//     from_vr = from_vr->twin;
//     from_vr->next = vr_v1;
//     vr_v1->prev = from_vr;

//     from_v1 = from_v1->twin;
//     from_v1->next = v1_vr;
//     v1_vr->prev = from_v1;
//     std::cout << "twin v1 : " << from_v1->origin->index << '\n';
//     std::cout << "twin vr : " << from_vr->origin->index << '\n';
//     //next of new edges to corresponding edges
  
//     back_v1 = back_v1->twin;
//     back_v1->prev = vr_v1;
//     vr_v1->next = back_v1;

//     back_vr = back_vr->twin;
//     back_vr->prev = v1_vr;
//     v1_vr->next = back_vr;
//     std::cout << "back twin v1 : " << back_v1->origin->index << '\n';
//     std::cout << "back twin vr : " << back_vr->origin->index << '\n';
//     std::cout << "back twin v1 : " << back_v1->next->origin->index << '\n';
//     std::cout << "back twin vr : " << back_vr->next->origin->index << '\n';
    
// }

// void decompose(const DCEL &dcel) {
//     int n = dcel.n;
//     std::deque<std::deque<Vertex *>> L;
//     std::deque<Vertex *> cur, notches = get_notches(dcel.polygon) , P = dcel.polygon;
//     cur.push_front(dcel.polygon[0]);
//     L.push_front(cur);
//     int m = 1;
//     while(n > 3) {
//         Vertex *v1 = L[m - 1].back();
//         Vertex *v2 = next_vertex(v2);
//         cur.clear();
//         cur.push_back(v1); cur.push_back(v2);
//         L.push_back(cur); // L[m] inserted
        

//         Vertex *pre = v1;
//         Vertex *now = v2;
//         Vertex *nxt = next_vertex(v2);
//         while (check_notch(pre, now, nxt, v1, v2) and (int)L[m].size() < n) {
//             L[m].push_back(nxt);
//             pre = now;
//             now = nxt;
//             nxt = next_vertex(nxt);
//         }    

//         if((int)L[m].size() != n) {
//             std::deque<Vertex*>LPVS;
//             for(auto notch : notches) {
//                 bool in = false;
//                 for(auto v : L[m]) {
//                     if(v == notch) {
//                         in = true;
//                         break;
//                     }
//                 }
//                 if(!in) LPVS.push_back(notch);
//             }
//             while(!LPVS.empty()) {
//                 auto rect = get_rectangle(L[m]);
//                 bool backward = false;
//                 do {
//                     Vertex *v = LPVS.front();
//                     if(!inside_rectangle(rect , v->point)) 
//                         LPVS.pop_front();
//                 } while(!backward and !LPVS.empty());

//                 if(!LPVS.empty()) {
//                     Vertex *v = LPVS.front();
//                     // Inside rectangle not sure ? 
//                     if(inside_rectangle(rect , v->point)) {
//                         std::deque<Vertex*> VTR;
//                         auto line = get_line(v1->point , v->point);
//                         auto bck = L[m].back();
//                         for(auto u : L[m]) {
//                             if(same_side_semiplane(line , u->point , bck->point))
//                                 VTR.push_back(u);
//                         }
//                         L[m] = VTR;
//                         backward = true;
//                         LPVS.pop_front();
//                     }
//                 }
//             }

//             if(L[m].back() != v2) {

                
//                 int sz = (int)L[m].size();
//                 n = n - sz + 2;
//             }
//             m++;
//         }

//     }
// }
