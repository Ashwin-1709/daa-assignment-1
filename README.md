# CS F364 -  Design and Analysis of Algorithms

### Objective: Decomposing any arbitrary polygon into convex polygons
In this assignment we have implemented the algorithm[1] described in the following paper: </br>
[1] Fernández, J., Cánovas, L., & Pelegrın, B. (2000). Algorithms for the decomposition of a polygon into 
convex polygons. European Journal of Operational Research, 121(2), 330-342. </br>
[Original Paper Link](https://doi.org/10.1016/S0377-2217(99)00033-8)
</br>
#### Doubly Connected Edge List (DCEL)
The decomposition is stored in a Doubly Connected Edge List (DCEL) Data Structure.
DCEL consists of three main sub-data-structures, namely Vertex, Edge and Face. </br>
![Screenshot 2023-05-12 at 16-24-22 lect10-dcel pdf](https://github.com/Ashwin-1709/DAA-Assignment-1/assets/98446038/8f28bba2-e826-4bd9-a3f7-88cc48f7480e)

#### Visualisation of the decomposition is written in python using matplotlib

## How to run : 
1. Install and configure Ninja, Cmake for the project.
2. Once configured, run the bash script for building ```./scripts/build.sh```
3. Input Format : Number of vertices of polygon (N) in first line and coordinates of points of polygon in subsequent N lines ( **in clockwise order only** )
4. To run use the bash script run.sh in scripts folder ```./scripts/run.sh test_file.txt```
