//
// Created by Home on 14/10/2018.
//

#include "../header/Triangle.h"

Triangle::Triangle(const Point& A, const Point& B, const Point& C, unsigned int materialId) {

    this->p1 = A;
    this->p2 = B;
    this->p3 = C;

    this->_materialId = materialId;
}
