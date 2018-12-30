//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H

#include "Point.h"
#include "Vector.h"
#include "Material.h"

class Triangle {

public:
    Point p1, p2, p3;

    Vector<float> normal;
    unsigned int id;
    unsigned int meshId;
    Material material;
    Triangle(const Point& A, const Point& B, const Point& C, unsigned int id);

    void setNormal(double x, double y, double z) {
        normal = Vector<float>(x,y,z);
    }

    ~Triangle() = default;

    inline friend std::ostream& operator<<(std::ostream& os, const Triangle& t){
        os << "(Triangle) : " << t.p1 << "," << t.p2 << "," << t.p3 ;
        return os;
    }
};


#endif //RAYTRACING_TRIANGLE_H
