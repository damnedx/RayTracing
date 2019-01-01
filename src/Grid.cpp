//
// Created by Home on 31/12/2018.
//

#include "../header/Grid.h"
#define LAMBDA 3


// init size and resolution grid
Grid::Grid(const vector<Triangle>& mesh) {

    // compute grid resolution following "A Parallel Ray Tracing Computer" article

    unsigned int totalTriangles = mesh.size();
    Bbox meshBoundingBox = this->getSceneBoudingBox(mesh);
    Point boundingBoxSize = meshBoundingBox.max - meshBoundingBox.min;
    Vector<double> size = Vector<double>(boundingBoxSize.x, boundingBoxSize.y, boundingBoxSize.z);

    double coeff_grid = powf(((LAMBDA * totalTriangles)/(size.vx * size.vy *size.vz)), 1/3.);

    this->gridResolution = Vector<int>(size.vx * coeff_grid,size.vy * coeff_grid,size.vz * coeff_grid);

    this->cellDimension = size / Vector<double>(this->gridResolution.vx,this->gridResolution.vy,this->gridResolution.vz);

    // insert triangles inside the grid
    this->fillGrid(mesh);


}
template<class T>
const T& clamp(const T& x, const T& lower, const T& upper) {
    return min(upper, max(x, lower));
}
void Grid::fillGrid(const vector<Triangle>& mesh){

    Bbox bbox = this->getSceneBoudingBox(mesh);

    for(auto& t : mesh){
        Point min = (t.getBoundingBox().min - bbox.min)  / Point(this->cellDimension.vx, this->cellDimension.vy, this->cellDimension.vz);
        Point max = (t.getBoundingBox().max - bbox.min) / Point(this->cellDimension.vx, this->cellDimension.vy, this->cellDimension.vz);

        int zmin = clamp<int>(std::floor(min.z), 0, this->gridResolution.vz - 1);
        int zmax = clamp<int>(std::floor(max.z), 0, this->gridResolution.vz - 1);
        int ymin = clamp<int>(std::floor(min.y), 0, this->gridResolution.vy - 1);
        int ymax = clamp<int>(std::floor(max.y), 0, this->gridResolution.vy - 1);
        int xmin = clamp<int>(std::floor(min.x), 0, this->gridResolution.vx - 1);
        int xmax = clamp<int>(std::floor(max.x), 0, this->gridResolution.vx - 1);

        for (int z = zmin; z <= zmax; ++z) {
            for (int y = ymin; y <= ymax; ++y) {
                for (int x = xmin; x <= xmax; ++x) {
                    Point p(x,y,z);
                    this->voxelTriangles[p].emplace_back(t);
                }
            }
        }
    }
}
Bbox Grid::getSceneBoudingBox(const vector<Triangle>& mesh) const {

    Bbox b = mesh[0].getBoundingBox();
    for (auto& t : mesh) {
        b.min.x = min(b.min.x, t.getBoundingBox().min.x);
        b.min.y = min(b.min.y, t.getBoundingBox().min.y);
        b.min.z = min(b.min.z, t.getBoundingBox().min.z);

        b.max.x = max(b.max.x, t.getBoundingBox().max.x);
        b.max.y = max(b.max.y, t.getBoundingBox().max.y);
        b.max.z = max(b.max.z, t.getBoundingBox().max.z);

    }

    return b;
}


