//
// Created by Home on 02/11/2018.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "Vector.h"
#include "Point.h"
#include "Triangle.h"

class Ray {
public:
    Point pSource;
    Vector<float> dir;

    Ray(const Point& o, const Vector<float>& dir);
    Point ray_position(float t) const;

    bool intersectTriangle(const Triangle& t, Point& pIntersection) const;

    float lightAtPoint(const Point& p, const Point &pLight, const Triangle &t) const;

    bool computeIntersections(Ray& r , Point &pIntersection, unsigned int &nearestTriangle) const;

    float computeLuminosityAtPoint(Ray &r, const Point& light, int &nearestTriangle);

    ~Ray() = default;

    inline friend std::ostream& operator<<(std::ostream& os, const Ray& r){
        os << "(Ray) : " << r.pSource << "," << r.dir;
        return os;
    }


};


#endif //RAYTRACING_RAY_H
