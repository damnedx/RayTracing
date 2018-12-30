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
    Vector<double> color;

    Material() = default;
    Material(float r, float g, float b, float reflection) {
        this->color = Vector<double>(r,g,b);
        this->reflection = reflection;
        this->ns = 0;
    };
    ~Material() = default;

    void setMaterial(Vector<double> ks,  Vector<double> kd, Vector<double> ka, float ns) {
        this->ks = ks;
        this->kd = kd;
        this->ka = ka;
        this->ns = ns;

        this->color = Vector<double>(1,1,1);
    }

    inline friend ostream& operator<<(ostream& os, const Material& m){
        os << "Material : (R,G,B) = (" << m.color << ") Reflection : " << m.reflection;
        return os;
    }

};


#endif //RAYTRACING_MATERIAL_H
