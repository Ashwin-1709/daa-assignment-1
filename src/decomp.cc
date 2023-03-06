#include "decomp.hh"
#include "dbg.hh"
#include <deque>

auto decompose(const Polygon &polygon) -> DecompData {
    // init
    usize n = polygon.n_vertices;
    std::deque<std::deque<Vertex *>> L;

    // Step 1
    std::deque<Vertex *> cur, P(begin(polygon.vertices), end(polygon.vertices));
    // Step 2
    cur.push_front(polygon.vertices[0]);
    L.push_front(cur);
    usize m = 1;

    // init
    std::set<Face *> decomposed_polygons = {polygon.inner_end};
    Face *cur_polygon = polygon.inner_end;
    std::map<Face *, usize> face_id;
    std::map<usize, Face *> inv_face_id;
    std::map<usize, bool> LDP;
    std::map<usize, usize> LUP;
    usize cur_id = 0;
    face_id[cur_polygon] = cur_id++;
    inv_face_id[face_id[cur_polygon]] = cur_polygon;
    std::map<Vertex *, std::vector<std::pair<usize, Vertex *>>> LP;
    std::vector<std::array<Vertex *, 2>> LLE;

    // Step 3
    while (n > 3) {
        usize i = 1;
        // 3.1
        Vertex *v1 = L[m - 1].back();
        Vertex *v2 = P[i];
        cur.clear();
        // 3.2
        cur.push_back(v1);
        cur.push_back(v2);
        L.push_back(cur);

        // 3.3
        while (L[m].size() < n and
               check_notch(P[i - 1], P[i], P[i + 1], v1, v2)) {
            L[m].push_back(P[i + 1]);
            i++;
        }

        // 3.4
        if (L[m].size() != P.size()) {
            auto notch = get_notches(P);
            // 3.4.1
            std::deque<Vertex *> LPVS = get_LPVS(notch, L[m], P);
            // 3.4.2
            while (!LPVS.empty()) {
                bool backward = false;
                auto rect = get_rectangle(L[m]);
                while (!backward and !LPVS.empty()) {
                    dbg(LPVS.size());
                    dbg(LPVS.front());
                    while (!LPVS.empty()) {
                        if (!inside_rectangle(rect, LPVS.front()->point)) {
                            LPVS.pop_front();
                        } else {
                            break;
                        }
                    }
                    if (!LPVS.empty()) {
                        auto inside = is_inside_polygon(L[m], LPVS.front());
                        if (inside) {
                            std::deque<Vertex *> VTR;
                            auto line =
                                get_line(v1->point, LPVS.front()->point);
                            auto bck = L[m].back();
                            for (auto u : L[m]) {
                                if (!same_side_semiplane(line, u->point,
                                                         bck->point) or
                                    u == v1) {
                                    VTR.push_back(u);
                                }
                            }
                            L[m].swap(VTR);
                            backward = true;
                        }
                        if (!LPVS.empty())
                            LPVS.pop_front();
                    }
                }
                if (LPVS.empty())
                    break;
            }
        }

        // 3.5
        if (L[m].back() != v2) {
            if (L[m].size() != n) {
                Face *new_polygon =
                    split_face(L[m].front(), L[m].back(), cur_polygon);
                decomposed_polygons.insert(new_polygon);
                cur_polygon = new_polygon;
                face_id[new_polygon] = cur_id++;
                inv_face_id[face_id[new_polygon]] = new_polygon;
                LLE.push_back({L[m].front(), L[m].back()});
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
        // 3.6
        m++;
    }

    for (auto &faces : decomposed_polygons) {
        Edge *now = faces->edge;
        usize id = face_id[faces];
        do {
            if (now->next->origin != next_vertex(now->origin))
                LP[now->origin].push_back({id, now->next->origin});
            now = now->next;
        } while (now != faces->edge);
    }

    return {decomposed_polygons, LP, LLE, inv_face_id, LDP, LUP};
}
