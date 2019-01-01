//
// Created by Home on 31/12/2018.
//

#include "../header/Grid.h"
#include "../header/Ray.h"
#include "../header/SceneReader.h"

#define LAMBDA 3

map<Point, vector<Triangle>> Grid::voxelTriangles;

Vector<int> Grid::gridResolution;
Vector<double> Grid::cellDimension;
Bbox Grid::bbox;

// init size and resolution grid
Grid::Grid(const vector<Triangle>& mesh) {

    // compute grid resolution following "A Parallel Ray Tracing Computer" article

    unsigned int totalTriangles = mesh.size();
    this->bbox = this->getSceneBoudingBox(mesh);
    Point boundingBoxSize = this->bbox.max - this->bbox.min;
    Vector<double> size = Vector<double>(boundingBoxSize.x, boundingBoxSize.y, boundingBoxSize.z);

    double coeff_grid = powf(((LAMBDA * totalTriangles)/(size.vx * size.vy *size.vz)), 1/3.);

    this->gridResolution = Vector<int>(size.vx * coeff_grid,size.vy * coeff_grid,1);

    this->cellDimension = size / Vector<double>(this->gridResolution.vx,this->gridResolution.vy,this->gridResolution.vz);

    // insert triangles inside the grid
    this->fillGrid(mesh);


}
template<class T>
const T& clamp(const T& x, const T& lower, const T& upper) {
    return min(upper, max(x, lower));
}
void Grid::fillGrid(const vector<Triangle>& mesh){

    for(auto& t : mesh){
        Point min = (t.getBoundingBox().min - this->bbox.min)  / Point(this->cellDimension.vx, this->cellDimension.vy, this->cellDimension.vz);
        Point max = (t.getBoundingBox().max - this->bbox.min) / Point(this->cellDimension.vx, this->cellDimension.vy, this->cellDimension.vz);

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
                    voxelTriangles[p].emplace_back(t);
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

vector<Triangle> Grid::getTrianglesDDA(Ray r){

    vector<Triangle> v;

    Vector<double> invDir = 1. / r.dir;
    Vector<double> sign(r.dir.vx < 0, r.dir.vy < 0, r.dir.vz < 0);
    float tHitBox;

    if (!r.intersectBbox(bbox, invDir, sign, tHitBox))
        return v;

    Vector<double> exit, step, cell;
    Vector<double> deltaT, nextCrossingT;
    for (int i = 0; i < 3; ++i) {
        // convert ray starting point to cell coordinates
        float rayOrigCell = ((r.pSource[i] + r.dir[i] * tHitBox) -  bbox[0][i]);
        cell[i] = clamp<int>(std::floor(rayOrigCell / cellDimension[i]), 0, gridResolution[i] - 1);
        if (r.dir[i] < 0) {
            deltaT[i] = -cellDimension[i] * invDir[i];
            nextCrossingT[i] = tHitBox + (cell[i] * cellDimension[i] - rayOrigCell) * invDir[i];
            exit[i] = -1;
            step[i] = -1;
        }
        else {
            deltaT[i] = cellDimension[i] * invDir[i];
            nextCrossingT[i] = tHitBox + ((cell[i] + 1)  * cellDimension[i] - rayOrigCell) * invDir[i];
            exit[i] = gridResolution[i];
            step[i] = 1;
        }
    }
    float tHit = 0;
    while (1) {
        Point p(cell[0], cell[1], cell[2]);

        if (voxelTriangles.find(p) != voxelTriangles.end() )
        {
            int triangleId;
            bool has_inter = r.computeIntersections2(r, voxelTriangles[p], tHit, triangleId);
            if(has_inter) {
                v.emplace_back(SceneReader::allTriangles[triangleId]);
            }
        }

        uint8_t k =
                ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
                ((nextCrossingT[0] < nextCrossingT[2]) << 1) +
                ((nextCrossingT[1] < nextCrossingT[2]));
        static const uint8_t map[8] = {2, 1, 2, 1, 2, 2, 0, 0};
        uint8_t axis = map[k];

        if (tHit < nextCrossingT[axis]) break;
        cell[axis] += step[axis];
        if (cell[axis] == exit[axis]) break;
        nextCrossingT[axis] += deltaT[axis];

    }

    return v;
}

