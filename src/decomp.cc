#include "decomp.hh"
#include "dbg.hh"
#include <deque>

std::set<Face *> decompose(Polygon *polygon) {
    usize n = polygon->n_vertices, m = 1;
    std::deque<std::deque<Vertex *>> L;
    std::deque<Vertex *> cur,
        P(begin(polygon->vertices), end(polygon->vertices));
    cur.push_front(polygon->vertices[0]);
    L.push_front(cur); // L0 <- {v1}
    std::set<Face *> decomposed_polygons = {polygon->inner_end};
    Face *cur_polygon = polygon->inner_end;
    while (n > 3) {
        usize i = 1;
        Vertex *v1 = L[m - 1].back();
        Vertex *v2 = P[i];
        cur.clear();
        cur.push_back(v1);
        cur.push_back(v2);
        L.push_back(cur); // L[m] inserted

        while (L[m].size() < n and
               check_notch(P[i - 1], P[i], P[i + 1], v1, v2)) {
            L[m].push_back(P[i + 1]);
            i++;
        }

        if (L[m].size() != P.size()) {
            auto notch = get_notches(P);
            std::deque<Vertex *> LPVS = get_LPVS(notch, L[m], P);
            while (!LPVS.empty()) {
                bool backward = false;
                auto rect = get_rectangle(L[m]);
                while (!backward and !LPVS.empty()) {
                    while (!LPVS.empty() and
                           !inside_rectangle(rect, LPVS.front()->point))
                        LPVS.pop_front();
                    if (!LPVS.empty()) {
                        auto inside = is_inside_polygon(L[m], LPVS.front());
                        if (inside) {
                            std::deque<Vertex *> VTR;
                            auto line = get_line(v1->point, LPVS.front()->point);
                            auto bck = L[m].back();
                            for (auto u : L[m]) {
                                if (!same_side_semiplane(line, u->point,bck->point) or u == v1) {
                                    VTR.push_back(u);
                                }
                            }
                            L[m].swap(VTR);
                            backward = true;
                            LPVS.pop_front();
                        }
                    }
                }
                if (LPVS.empty())
                    break;
            }
        }

        if (L[m].back() != v2) {
            if (L[m].size() != n) {
                Face *new_polygon =
                    split_face(L[m].front(), L[m].back(), cur_polygon);
                decomposed_polygons.insert(new_polygon);
                cur_polygon = new_polygon;
            }
            Vertex *first = L[m].front();
            Vertex *last = L[m].back();
            std::deque<Vertex *> nxt_iter;
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
            P.pop_front();
            P.pop_front();
            P.push_back(first);
            P.push_front(last);
        }
        m++;
    }
    return decomposed_polygons;
}
