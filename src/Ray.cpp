//
// Created by Home on 02/11/2018.
//

#include "../header/Ray.h"
#define INTENSITY 10
Ray::Ray(const Point& O, const Vector<float>& dir) {

    this->pSource = O;
    this->dir = dir;

}

Point Ray::ray_position(float t) {
    Vector<float> proj = t*this->dir;
    return this->pSource + Point(proj.vx, proj.vy, proj.vz);
}

bool Ray::intersectTriangle(const Triangle& t, Point& pIntersection){

    const float EPSILON = 0.0000001;

    Vector<float> vertex0(t.p1.x, t.p1.y, t.p1.z);
    Vector<float> vertex1(t.p2.x, t.p2.y, t.p2.z);
    Vector<float> vertex2(t.p3.x, t.p3.y, t.p3.z);

    float a,f,u,v;

    Vector<float> edge1 = vertex1 - vertex0;
    Vector<float> edge2 = vertex2 - vertex0;

    Vector<float>h = this->dir^edge2;

    a = edge1*h;
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;

    Vector<float> s = Vector<float>(this->pSource.x, this->pSource.y, this->pSource.z) - vertex0;

    u = f * (s*h);
    if (u < 0.0 || u > 1.0)
        return false;

    Vector<float> q = s ^ edge1;

    v = f * this->dir * q;
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute p to find out where the intersection point is on the line.
    float p = f * (edge2*q);

    if (p > EPSILON) // ray intersection
    {
        pIntersection = this->ray_position(p);
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}

float Ray::lightAtPoint(const Point &p, const Point &pLight, const Triangle &t) {

    Vector<float> v1(t.p2.x - t.p1.x, t.p2.y - t.p1.y, t.p2.z - t.p1.z);
    Vector<float> v2(t.p3.x - t.p1.x, t.p3.y - t.p1.y, t.p3.z - t.p1.z);
    Vector<float>vOriginTriangle = v1^v2;
    Vector<float> vTriangleLight(p, pLight);

    float angleRayLight = vOriginTriangle.normalizeVector() * vTriangleLight.normalizeVector();

    return  (INTENSITY * angleRayLight);
}
