//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H

#include <iostream>

template<typename T>
class Vector{

public:
    T vx;
    T vy;
    T vz;

    Vector() = default;

    Vector(T x, T y, T z);

    ~Vector() = default;

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
inline Vector<T> operator*(const Vector<T>& v, const T& value){
    return Vector<T>(v.vx * value, v.vy * value, v.vz * value);
}
template<typename T>
inline Vector<T> operator*(const T& value, const Vector<T>& v){
    return Vector<T>(v.vx * value, v.vy * value, v.vz * value);
}

template<typename T>
inline Vector<T> operator*(const Vector<T>& v1, const Vector<T>& v2){
    return Vector<T>(v1.vx * v1.vx, v1.vy * v2.vy, v1.vz * v2.vz);
}
#endif //RAYTRACING_VECTOR_H
