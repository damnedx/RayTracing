//
// Created by Home on 02/11/2018.
//

#include "../header/Ray.h"

Ray::Ray(const Point& O, const Vector<float>& dir) {

    this->pSource = O;
    this->dir = dir;

}

Point Ray::ray_position(float t) {
    Vector<float> proj = t*this->dir;
    return this->pSource + Point(proj.vx, proj.vy, proj.vz);
}