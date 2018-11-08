//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H

#include <iostream>
#include "Point.h"
#include <cmath>

template<typename T>
class Vector{

public:
    T vx;
    T vy;
    T vz;

    Vector() = default;
    Vector(T x, T y, T z);
    Vector(Point p1, Point p2);

    ~Vector() = default;

    Vector<T> normalizeVector(){
        float norm = this->getNorm();
        return Vector<float>(this->vx / norm, this->vy / norm, this->vz / norm);
    }
    float getNorm(){
        return sqrt(this->vx * this->vx + this->vy * this->vy + this->vz * this->vz);
    }

    inline friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v){
        os << "Vector : (x,y,z) = (" << v.vx << "," << v.vy << "," << v.vz << ")";
        return os;
    }

};

template<typename T>
Vector<T>::Vector(T x, T y, T z){
    this->vx = x;
    this->vy = y;
    this->vz = z;
}
template<typename T>
Vector<T>::Vector(Point p1, Point p2){
    this->vx = p2.x - p1.x;
    this->vy = p2.y - p1.y;
    this->vz = p2.z - p1.z;
}

template<typename T>
inline Vector<T> operator*(const Vector<T>& v, const T& value){
    return Vector<T>(v.vx * value, v.vy * value, v.vz * value);
}
template<typename T>
inline Vector<T> operator*(const T& value, const Vector<T>& v){
    return Vector<T>(v.vx * value, v.vy * value, v.vz * value);
}

// dot product
template<typename T>
inline T operator*(const Vector<T>& v1, const Vector<T>& v2){
    return v1.vx * v2.vx + v1.vy * v2.vy + v1.vz * v2.vz;
}
template<typename T>
inline Vector<T> operator/(const Vector<T>& v1, const Vector<T>& v2){
    return Vector<T>(v1.vx / v2.vx, v1.vy / v2.vy, v1.vz / v2.vz);
}
template<typename T>
inline Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2){
    return Vector<T>(v1.vx + v2.vx, v1.vy + v2.vy, v1.vz + v2.vz);
}
template<typename T>
inline Vector<T> operator-(const Vector<T>& v1, const Vector<T>& v2){
    return Vector<T>(v1.vx - v2.vx, v1.vy - v2.vy, v1.vz - v2.vz);
}
template<typename T>
inline Vector<T> operator-(const Vector<T>& v1){
    return Vector<T>(-v1.vx, -v1.vy, -v1.vz);
}

// cross product
template<typename T>
inline Vector<T> operator^(const Vector<T>& v1, const Vector<T>& v2){
    return Vector<T>(v1.vy * v2.vz - v2.vy*v1.vz, v2.vx*v1.vz - v1.vx*v2.vz, v1.vx*v2.vy - v2.vx*v1.vy);
}
#endif //RAYTRACING_VECTOR_H
