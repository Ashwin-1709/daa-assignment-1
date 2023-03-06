#ifndef DECOMP_H
#define DECOMP_H
#include "typedefs.hh"
#include "utils.hh"
#include <deque>

struct DecompData {
    std::set<Face *> faces;
    std::map<Vertex *, std::vector<std::pair<usize, Vertex *>>> LP;
    std::vector<std::array<Vertex *, 2>> LLE;
    std::map<usize, Face *> inv_face_id;
    std::map<usize, bool> LDP;
    std::map<usize, usize> LUP;
    DecompData(std::set<Face *> a_faces,
               std::map<Vertex *, std::vector<std::pair<usize, Vertex *>>> a_LP,
               std::vector<std::array<Vertex *, 2>> a_LLE,
               std::map<usize, Face *> a_inv_face_id,
               std::map<usize, bool> a_LDP, std::map<usize, usize> a_LUP)
        : faces(std::move(a_faces)), LP(std::move(a_LP)), LLE(std::move(a_LLE)),
          inv_face_id(std::move(a_inv_face_id)), LDP(std::move(a_LDP)),
          LUP(std::move(a_LUP)) {}
};

DecompData decompose(const Polygon &polygon);
std::set<Face *> merge(DecompData &polygon);

#endif // DECOMP_H
