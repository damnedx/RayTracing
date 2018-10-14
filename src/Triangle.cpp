//
// Created by Home on 14/10/2018.
//

#include "../header/Triangle.h"

Triangle::Triangle(Point A, Point B, Point C, unsigned int materialId) {

    this->A = A;
    this->B = B;
    this->C = C;

    this->_materialId = materialId;
}
