#ifndef DCEL_H
#define DCEL_H
#include "typedefs.hh"
#include <array>
#include <deque>

class Vertex;
class Edge;
class Face {
  public:
    Edge *edge;
    /*!< Representative edge of the face */
};

class Edge {
  public:
    Vertex *origin;
    /*!< The Vertex the Edge starts from */
    Edge *twin;
    /*!< The vertex with source and destination swapped */
    Face *left_face;
    /*!< The Face enclosed by the Edge */
    Edge *next;
    /*!< The next Edge of the edge */
    Edge *prev;
    /*!< The previous Edge of the edge */
};

class Point {
  public:
    double x;          /*!< The x coordinate of the Point */
    double y;          /*!< The y coordinate of the Point */
    Point() = default; /*!< Default constructor */
    Point(double x_arg, double y_arg) : x(x_arg), y(y_arg) {}
    /*!< Constructor taking coordinates */
};

class Vertex {
  public:
    Point point; /*!< The coordinates of the Vertex, represented as a Point */
    usize index; /*!< The index of the Vertex */
    Edge *incident_edge; /*!< Edge originating at this Vertex*/
    Vertex(Point point_, usize index_) : point(point_), index(index_) {}
    /*!< Constructor taking Point and index */
};

class Polygon {
  public:
    Face *open_end;
    /*!< Face corresponding to the open end of polygon*/
    Face *inner_end;
    /*!< Face corresponding to the inner end of polygon */
    std::deque<Vertex *> vertices; /*!< Deque of `Vertex`es of the Polygon */
    usize n_vertices;              /*!< Number of vertices in the Polygon */
    Polygon(const std::deque<Point> &point_list);
    /*!< Constructor taking list of `Point`s */
    Polygon();
    /*!< Default constructor */
};

#endif
