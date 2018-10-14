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
    Point A,B,C;

    Triangle(Point A, Point B, Point C, unsigned int materialId);
    ~Triangle() = default;

    inline friend std::ostream& operator<<(std::ostream& os, const Triangle& t){
        os << t.A << "," << t.B << "," << t.C ;
        return os;
    }
};


#endif //RAYTRACING_TRIANGLE_H
