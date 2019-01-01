//
// Created by Home on 14/10/2018.
//

#include "../header/Triangle.h"

Triangle::Triangle(const Point& A, const Point& B, const Point& C, unsigned int id) {

    this->p1 = A;
    this->p2 = B;
    this->p3 = C;

    this->id = id;

    this->pointVector = Vector<Point>(A,B,C);
}

Bbox Triangle::getBoundingBox() const {

    double min_x = min(min(this->p1.x, this->p2.x), this->p3.x);
    double min_y = min(min(this->p1.y, this->p2.y), this->p3.y);
    double min_z = min(min(this->p1.z, this->p2.z), this->p3.z);

    double max_x = max(max(this->p1.x, this->p2.x), this->p3.x);
    double max_y = max(max(this->p1.y, this->p2.y), this->p3.y);
    double max_z = max(max(this->p1.z, this->p2.z), this->p3.z);

    Bbox b;
    b.min = Point(min_x, min_y, min_z);
    b.max = Point(max_x, max_y, max_z);

    return b;
}