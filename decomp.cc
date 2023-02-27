#include "decomp.hh"
#include "bits/stdc++.h"

deque<deque<Vertex *>> decompose(Polygon *polygon) {
    usize n = polygon->n_vertices, m = 1;
    deque<deque<Vertex *>> L;
    deque<Vertex *> cur, P(begin(polygon->vertices), end(polygon->vertices));
    cur.push_front(polygon->vertices[0]);
    L.push_front(cur); // L0 <- {v1}

    while (n > 3) {
        // dbg(n);
        usize i = 1;
        Vertex *v1 = L[m - 1].back();
        Vertex *v2 = P[i];
        // dbg(v1->index , v2->index);
        // dbg("Exploring....");
        // dbg(v1->point.x , v1->point.y);
        // dbg(v2->point.x , v2->point.y);
        // for(usize i = 2 ; i < P.size() ; i++)
        //     dbg(P[i]->point.x , P[i]->point.y);
        cur.clear();
        cur.push_back(v1);
        cur.push_back(v2);
        L.push_back(cur); // L[m] inserted

        while (L[m].size() < n and
               check_notch(P[i - 1], P[i], P[i + 1], v1, v2)) {
            L[m].push_back(P[i + 1]);
            i++;
        }

        // dbg(L[m].size());
        if (L[m].size() != P.size()) {
            auto notch = get_notches(P);
            deque<Vertex *> LPVS = get_LPVS(notch, L[m], P);
            // dbg(LPVS.size());
            while (!LPVS.empty()) {
                bool backward = false;
                auto rect = get_rectangle(L[m]);
                // dbg("hhhh" , L[m].size());
                for (auto x : LPVS)
                    // dbg(x->point.x , x->point.y);
                    // dbg(rect[0].x , rect[0].y , rect[1].x , rect[1].y);
                    while (!backward and !LPVS.empty()) {
                        // dbg(backward);
                        while (!LPVS.empty() and
                               !inside_rectangle(rect, LPVS.front()->point))
                            LPVS.pop_front();
                        // dbg("here" , LPVS.size());
                        if (!LPVS.empty()) {
                            auto inside =
                                inside_rectangle(rect, LPVS.front()->point);
                            if (inside) {
                                std::deque<Vertex *> VTR;
                                auto line =
                                    get_line(v1->point, LPVS.front()->point);
                                // dbg("Line" , line[0] , line[1] , line[2]);
                                auto bck = L[m].back();
                                //  dbg("Back point" , LPVS.front()->point.x ,
                                //  LPVS.front()->point.y); dbg("bck" ,
                                //  bck->point.x , bck->point.y);
                                for (auto u : L[m]) {
                                    // dbg("U" , u->point.x , u->point.y);
                                    // dbg("same side ? " ,
                                    // same_side_semiplane(line , u->point ,
                                    // bck->point));
                                    if (!same_side_semiplane(line, u->point,
                                                             bck->point) or u == v1) {
                                        VTR.push_back(u);
                                    }
                                }
                                // dbg("After semiplane"   , L[m].size() ,
                                // VTR.size()); for(auto x : VTR)
                                //     dbg(x->point.x , x->point.y);
                                L[m].swap(VTR);
                                // dbg(VTR.size());
                                backward = true;
                                LPVS.pop_front();
                                // for(auto x : LPVS)
                                //     dbg(x->point.x , x->point.y);
                            }
                        }
                    }
                if (LPVS.empty())
                    break;
            }
        }

        if (L[m].back() != v2) {
            // add_edge(L[m].front() , L[m].back());
            // dbg("yes");
            Vertex *first = L[m].front();
            Vertex *last = L[m].back();
            deque<Vertex *> nxt_iter;
            for (auto vert : P) {
                bool in_L = false;
                for (auto s : L[m])
                    in_L |= (vert == s);
                if (in_L)
                    continue;
                nxt_iter.push_back(vert);
            }
            nxt_iter.push_front(last);
            nxt_iter.push_back(first);
            P.swap(nxt_iter);
            n = P.size();
        } else {
            Vertex *first = L[m].front();
            Vertex *last = L[m].back();
            // dbg(first->point.x , first->point.y);
            // dbg(last->point.x , last->point.y);
            P.pop_front();
            P.pop_front();
            P.push_back(first);
            P.push_front(last);
        }
        m++;
    }
    return L;
}
