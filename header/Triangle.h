//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H

#include "Point.h"


class Triangle {

private:
    unsigned int _materialId;
public:
    Point p1, p2, p3;

    Triangle(Point A, Point B, Point C, unsigned int materialId);
    ~Triangle() = default;

    inline friend std::ostream& operator<<(std::ostream& os, const Triangle& t){
        os << "(Triangle) : " << t.p1 << "," << t.p2 << "," << t.p3 ;
        return os;
    }
};


#endif //RAYTRACING_TRIANGLE_H
