//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include <iostream>
#include "Vector.h"
using namespace std;
class Material {
public:

    float reflection;
    float ns;
    Vector<double> ks, kd, ka;

    Material() = default;
    Material(float r, float g, float b, float reflection) {
        this->reflection = reflection;
        this->ns = 0;
    };
    ~Material() = default;

    void setMaterial(Vector<double> ks,  Vector<double> kd, Vector<double> ka, float ns) {
        this->ks = ks;
        this->kd = kd;
        this->ka = ka;
        this->ns = ns;

    }


};


#endif //RAYTRACING_MATERIAL_H
