//
// Created by Home on 31/12/2018.
//

#ifndef RAYTRACING_GRID_H
#define RAYTRACING_GRID_H


#include <vector>
#include <map>
#include <list>
#include "Vector.h"
#include "Triangle.h"
#include "Ray.h"


class Grid {
public:
    // grid resolution
    static Vector<int> gridResolution;
    static Vector<double> cellDimension;
    static Bbox bbox;

    static map<Point, vector<Triangle>> voxelTriangles;

    Grid() = default;
    Grid(const vector<Triangle>& mesh);
    Bbox getSceneBoudingBox(const vector<Triangle>& mesh) const;
    void fillGrid(const vector<Triangle>& mesh);
    static vector<Triangle> getTrianglesDDA(Ray r);
    ~Grid() = default;








};


#endif //RAYTRACING_GRID_H
