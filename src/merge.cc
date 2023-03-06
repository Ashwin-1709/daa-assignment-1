#include "merge.hh"
#include "decomp.hh"

auto merge(DecompData &decompdata) -> std::set<Face *> {
    std::vector<Face *> remove;
    auto &faces = decompdata.faces;
    auto &LDP = decompdata.LDP;
    auto &LUP = decompdata.LUP;
    auto &inv_face_id = decompdata.inv_face_id;
    const auto &LLE = decompdata.LLE;
    const auto &LP = decompdata.LP;
    for (const auto &f : faces) {
        if (is_collinear(f)) {
            remove.push_back(f);
}
    }

    for (auto &f : remove) {
        faces.erase(f);
    }

    usize m = decompdata.LLE.size();
    // Step 1
    usize NP = m + 1;

    // Step 2
    for (usize i = 0; i < NP; i++) {
        LDP[i] = true;
        LUP[i] = i;
    }

    // Step 3
    for (usize j = 0; j < m; j++) {
        // 3.1
        auto [Vs, Vt] = LLE[j];
        auto cond_1 = (LP.at(Vs).size() > 2 and LP.at(Vt).size() > 2);
        auto cond_2 = (LP.at(Vs).size() > 2 and is_convex(Vt));
        auto cond_3 = (LP.at(Vt).size() > 2 and is_convex(Vs));
        auto cond_4 = (is_convex(Vt) and is_convex(Vs));
        auto eval = cond_1 or cond_2 or cond_3 or cond_4;
        if (!eval) {
            continue;
        }
        Vertex *j2 = Vt;
        Vertex *i2 = Vs;
        Vertex *j3 = next_vertex(Vt, inv_face_id[j]);
        Vertex *i1 = prev_vertex(Vs, inv_face_id[j]);
        usize f_id = 0;
        bool found = false;
        for (const auto &[id, vt] : LP.at(Vt)) {
            if (vt == Vs) {
                f_id = id, found = true;
}
        }
        Vertex *j1 = prev_vertex(Vt, inv_face_id[f_id]);
        Vertex *i3 = next_vertex(Vs, inv_face_id[f_id]);
        auto ang_1 = angle(i1->point, i2->point, i3->point);
        auto ang_2 = angle(j1->point, j2->point, j3->point);
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
                if (LUP[h] == j or LUP[h] == f_id) {
                    LUP[h] = NP;
}
            }
        }
    }

    return faces;
}
