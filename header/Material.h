//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include <iostream>

class Material {
public:

    float r,g,b, reflection;

    Material(float r, float g, float b, float reflection) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->reflection = reflection;
    };
    ~Material() = default;
    inline friend ostream& operator<<(ostream& os, const Material& m){
        os << "Material : (R,G,B) = (" << m.r << "," << m.g << "," << m.b << ") Reflection : " << m.reflection;
        return os;
    }

};


#endif //RAYTRACING_MATERIAL_H
