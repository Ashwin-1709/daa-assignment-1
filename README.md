# CS F364 -  Design and Analysis of Algorithms

### Objective: Decomposing any arbitrary polygon into convex polygons
In this assignment we have implemented the algorithm described in the following paper (decomposition + merging):

[Fernández, J., Cánovas, L., & Pelegrın, B. (2000). Algorithms for the decomposition of a polygon into convex polygons. European Journal of Operational Research, 121(2), 330-342](https://doi.org/10.1016/S0377-2217(99)00033-8)
#### Doubly Connected Edge List (DCEL)
The decomposition is stored in a Doubly Connected Edge List (DCEL) Data Structure.
DCEL consists of three main sub-data-structures, namely Vertex, Edge and Face. </br>
![Screenshot 2023-05-12 at 16-39-04 lect10-dcel pdf](https://github.com/Ashwin-1709/DAA-Assignment-1/assets/98446038/7702f964-99c4-4234-9790-35f590bd47c8)

#### Visualisation of the decomposition is written in python using matplotlib


## Building and running:
1. Install CMake.
2. Run `cmake . -B build` to generate the makefile.
3. Run `make -C build` to build.
4. `./build/polygon_decomp` to run.

    Input format: Number of vertices of polygon $N$ in first line and coordinates of points of polygon in subsequent $N$ lines (**in clockwise order only**)

You can use `cmake --build build --target doxygen` to build the docs, which will be available at `build/html/index.html`
