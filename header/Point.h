//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H


#include <iostream>
#include <tuple>

class Point{

public:
    double x;
    double y;
    double z;

    Point() = default;
    Point(double x, double y, double z);
    ~Point() = default;

    bool operator <( const Point &p2 ) const
    {
        return std::tie(x, y, z) < std::tie(p2.x, p2.y, p2.z);
    }

    double operator[] (int i) {
        if(i == 0)
            return x;
        if(i==1)
            return y;
        if(i==2)
            return z;
    }


    inline friend std::ostream& operator<<(std::ostream& os, const Point& p){
        os << "Point : (x,y,z) = (" << p.x << "," <<p.y << "," << p.z << ")";
        return os;
    }


};
template<typename T>
inline Point operator+(const T& t, const Point& p2){
    return Point(t + p2.x, t + p2.y, t + p2.z);
}
inline Point operator+(const Point& p1, const Point& p2){
    return Point(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}
inline Point operator*(const Point& p1, const Point& p2){
    return Point(p1.x * p2.x, p1.y * p2.y, p1.z * p2.z);
}
inline Point operator-(const Point& p1, const Point& p2){
    return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}
inline Point operator/(const Point& p1, const Point& p2){
    return Point(p1.x / p2.x, p1.y / p2.y, p1.z / p2.z);
}
inline bool operator==(const Point& p1, const Point& p2){
    return (p1.x == p2.x &&  p1.y == p2.y && p1.z == p2.z);
}
inline bool operator!=(const Point& p1, const Point& p2){
    return (p1.x != p2.x ||  p1.y!= p2.y || p1.z != p2.z);
}
inline bool operator<=(const Point& p1, const Point& p2){
    return (p1.x <= p2.x &&  p1.y <= p2.y && p1.z <= p2.z);
}
inline bool operator>=(const Point& p1, const Point& p2){
    return (p1.x >= p2.x &&  p1.y >= p2.y && p1.z >= p2.z);
}
#endif //RAYTRACING_POINT_H
