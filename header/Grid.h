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

class Grid {
public:
    // grid resolution
    Vector<int> gridResolution;
    Vector<double> cellDimension;

    map<Point, list<Triangle>> voxelTriangles;

    Grid() = default;
    Grid(const vector<Triangle>& mesh);
    Bbox getSceneBoudingBox(const vector<Triangle>& mesh) const;
    void fillGrid(const vector<Triangle>& mesh);
    ~Grid() = default;








};


#endif //RAYTRACING_GRID_H
