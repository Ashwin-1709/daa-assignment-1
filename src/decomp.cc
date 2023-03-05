#include "decomp.hh"
#include "dbg.hh"
#include <deque>

std::vector<std::array<Vertex *, 2>> LLE;
std::map<Vertex *, std::vector<std::pair<usize, Vertex *>>> LP;
std::map<Face *, usize> face_id;
std::map<usize, Face *> inv_face_id;
std::map<usize, bool> LDP;
std::map<usize, usize> LUP;

std::set<Face *> decompose(Polygon *polygon) {
    usize n = polygon->n_vertices, m = 1;
    std::deque<std::deque<Vertex *>> L;
    std::deque<Vertex *> cur,
        P(begin(polygon->vertices), end(polygon->vertices));
    cur.push_front(polygon->vertices[0]);
    L.push_front(cur); // L0 <- {v1}
    std::set<Face *> decomposed_polygons = {polygon->inner_end};
    Face *cur_polygon = polygon->inner_end;

    usize cur_id = 0;
    face_id[cur_polygon] = cur_id++;
    inv_face_id[face_id[cur_polygon]] = cur_polygon;
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
                    // dbg(LPVS.size());
                    // dbg(LPVS.front());
                    while (!LPVS.empty()) {
                        if (!inside_rectangle(rect, LPVS.front()->point)) {
                            LPVS.pop_front();
                        } else {
                            break;
                        }
                    }
                    // dbg(LPVS.size());
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
    return decomposed_polygons;
}

std::set<Face *> merge(Polygon *polygon) {
    auto faces = decompose(polygon);
    std::vector<Face *> remove;
    for (auto &f : faces) {
        if (is_collinear(f))
            remove.push_back(f);
    }

    for (auto &f : remove)
        faces.erase(f);

    usize M = LLE.size();
    usize NP = M + 1;

    for (usize i = 0; i < NP; i++) {
        LDP[i] = true;
        LUP[i] = i;
    }

    for (usize j = 0; j < M; j++) {
        auto [Vs, Vt] = LLE[j];
        auto cond_1 = (LP[Vs].size() > 2 and LP[Vt].size() > 2);
        auto cond_2 = (LP[Vs].size() > 2 and is_convex(Vt));
        auto cond_3 = (LP[Vt].size() > 2 and is_convex(Vs));
        auto cond_4 = (is_convex(Vt) and is_convex(Vs));
        auto eval = cond_1 or cond_2 or cond_3 or cond_4;
        if(!eval) continue;
        Vertex *j2 = Vt, *i2 = Vs, *j3 = next_vertex(Vt, inv_face_id[j]),
               *i1 = prev_vertex(Vs, inv_face_id[j]);
        usize f_id = 0;
        bool found = false;
        for (auto &[id, vt] : LP[Vt]) {
            if (vt == Vs)
                f_id = id, found = true;
        }
        Vertex *j1 = prev_vertex(Vt, inv_face_id[f_id]);
        Vertex *i3 = next_vertex(Vs, inv_face_id[f_id]);
        // dbg(Vs->point.x , Vs->point.y);
        // dbg(j1->point.x , j1->point.y);
        // dbg(j2->point.x , j2->point.y);
        // dbg(j3->point.x , Vs->point.y);
        // dbg(Vt->point.x , Vt->point.y);
        // dbg(i1->point.x , i1->point.y);
        // dbg(i2->point.x , i2->point.y);
        // dbg(i3->point.x , i3->point.y);
        auto ang_1 = angle(i1->point, i2->point, i3->point);
        auto ang_2 = angle(j1->point, j2->point, j3->point);
        // dbg(ang_1 , ang_2);
        if (ang_1 > 180 and ang_2 > 180) {
            NP++;
            Face *new_face =
                merge_face(inv_face_id[LUP[j]], inv_face_id[LUP[f_id]]);
            faces.erase(inv_face_id[LUP[f_id]]);
            LDP[j] = false;
            LDP[f_id] = false;
            LDP[NP] = true;
            LUP[j] = NP;
            inv_face_id[NP] = new_face;
            LUP[f_id] = NP;
            for (usize h = 0; h < NP - 1; h++) {
                if (LUP[h] == j or LUP[h] == f_id)
                    LUP[h] = NP;
            }
        }
    }

    return faces;
}
