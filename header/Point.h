//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H


#include <iostream>

class Point{

public:
    float x;
    float y;
    float z;

    Point() = default;
    Point(float x, float y, float z);
    ~Point() = default;

    inline friend std::ostream& operator<<(std::ostream& os, const Point& p){
        os << "Point : (x,y,z) = (" << p.x << "," <<p.y << "," << p.z << ")";
        return os;
    }


};
#endif //RAYTRACING_POINT_H
