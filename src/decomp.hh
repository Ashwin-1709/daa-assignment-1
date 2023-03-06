#ifndef DECOMP_H
#define DECOMP_H
#include "typedefs.hh"
#include "utils.hh"
#include <deque>
#include <map>
#include <vector>

struct DecompData {
    std::set<Face *> faces; /*!< Set of decomposed polygons to merge */
    std::map<Vertex *, std::vector<std::pair<usize, Vertex *>>> LP;
    /*!< List of (index, vertex): (k, v) where LP[w] = (k, v) means v is the
    next vertex of w in the kth polygon but is not adjacent to w in the original
    polygon */
    std::vector<std::array<Vertex *, 2>>
        LLE; /*!< List of diagonals of the partition */
    std::map<usize, Face *> inv_face_id; /*!< Maps polygon index to Face */
    std::map<usize, bool> LDP;  /*!< List which stores if a polygon with a given
                                   index is in the final list of polygons */
    std::map<usize, usize> LUP; /*!< Map of (polygon index, polygon index): (i,
                                   j) means polygon i is part of polygon j */
    DecompData(std::set<Face *> a_faces,
               std::map<Vertex *, std::vector<std::pair<usize, Vertex *>>> a_LP,
               std::vector<std::array<Vertex *, 2>> a_LLE,
               std::map<usize, Face *> a_inv_face_id,
               std::map<usize, bool> a_LDP, std::map<usize, usize> a_LUP)
        : faces(std::move(a_faces)), LP(std::move(a_LP)), LLE(std::move(a_LLE)),
          inv_face_id(std::move(a_inv_face_id)), LDP(std::move(a_LDP)),
          LUP(std::move(a_LUP)) {}
};

auto decompose(const Polygon &polygon) -> DecompData;

#endif // DECOMP_H
