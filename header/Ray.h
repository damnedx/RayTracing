//
// Created by Home on 02/11/2018.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include <vector>
#include "Vector.h"
#include "Point.h"
#include "Triangle.h"


class Ray {
public:
    Point pSource;
    Vector<double> dir;

    // just to compare w/o grid
    static int compute_intersection_1;
    static int compute_intersection_2;

    Ray(const Point& o, const Vector<double>& dir);
    Point ray_position(double t) const;

    bool intersectTriangle(const Triangle& t, Point& pIntersection, float &distance) const;


    bool intersectBbox(Bbox& b, Vector<double>& invDir, Vector<double>& sign, float& tHit);

    float lightAtPoint(const Point& p, const Point &pLight, const Triangle &t) const;

    bool computeIntersections(Ray& r , Point &pIntersection, int &nearestTriangle) const;

    bool computeIntersections2(Ray& r ,vector<Triangle> triangles, float &t, int &triangleId) const;

    Vector<double> computeLuminosityAtPoint(Ray &r, const Point& light,const Point& origin, int &nearestTriangle);

    ~Ray() = default;

    inline friend std::ostream& operator<<(std::ostream& os, const Ray& r){
        os << "(Ray) : " << r.pSource << "," << r.dir;
        return os;
    }


};


#endif //RAYTRACING_RAY_H
