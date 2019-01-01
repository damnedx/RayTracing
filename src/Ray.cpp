//
// Created by Home on 02/11/2018.
//

#include "../header/Ray.h"
#include "../header/SceneReader.h"

#define INTENSITY 10000
Ray::Ray(const Point& O, const Vector<double>& dir) {

    this->pSource = O;
    this->dir = dir;

}

Point Ray::ray_position(double t) const {
    Vector<double> proj = t * this->dir;
    return this->pSource + Point(proj.vx, proj.vy, proj.vz);
}

bool Ray::intersectTriangle(const Triangle& t, Point& pIntersection) const {

    const float EPSILON = 0.0000001;

    Vector<double> vertex0(t.p1.x, t.p1.y, t.p1.z);
    Vector<double> vertex1(t.p2.x, t.p2.y, t.p2.z);
    Vector<double> vertex2(t.p3.x, t.p3.y, t.p3.z);

    double a,f,u,v;

    Vector<double> edge1 = vertex1 - vertex0;
    Vector<double> edge2 = vertex2 - vertex0;

    Vector<double>h = this->dir^edge2;

    a = edge1*h;
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;

    Vector<double> s = Vector<double>(this->pSource.x, this->pSource.y, this->pSource.z) - vertex0;

    u = f * (s*h);
    if (u < 0.0 || u > 1.0)
        return false;

    Vector<double> q = s ^ edge1;

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

float Ray::lightAtPoint(const Point &p, const Point &pLight, const Triangle &t) const {

    Vector<float> v1(t.p1, t.p2);
    Vector<float> v2(t.p1, t.p3);
    Vector<float>N = (v1^v2);
    Vector<float> vTriangleLight(p, pLight);

    float angleRayLight = N.normalizeVector() * vTriangleLight.normalizeVector();

    return  (INTENSITY * angleRayLight);
}
bool Ray::computeIntersections(Ray &r, Point &pIntersection, int &nearestTriangle) const {

    bool has_intersection = false;

    Vector<float> minDistanceOriginTriangle(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    for (auto& t : SceneReader::allTriangles) {
        bool intersection = r.intersectTriangle(t, pIntersection);
        if(intersection){
            has_intersection = true;
            Vector<float> distanceOriginTriangle(r.pSource, pIntersection);
            if(distanceOriginTriangle.getNorm() < minDistanceOriginTriangle.getNorm()){
                minDistanceOriginTriangle = distanceOriginTriangle;
                nearestTriangle = t.id;
            }
        }
    }
    return has_intersection;
}

Vector<double> Ray::computeLuminosityAtPoint(Ray &r, const Point& light,const Point& origin, int &nearestTriangle) {

    Point pIntersection;
    int idNearestTriangle = -1;
    Vector<double> lDiffuse(0,0,0);
    Vector<double> lAmbient(0,0,0);
    Vector<double> lSpeculaire(0,0,0);

    // compute diffuse light
    bool intersection = r.computeIntersections(r, pIntersection, idNearestTriangle);
    nearestTriangle = idNearestTriangle;
    if (intersection) {
        Triangle nearestTriangle = SceneReader::allTriangles[idNearestTriangle];
        double coeff = r.lightAtPoint(pIntersection, light, nearestTriangle);
        Material mat = nearestTriangle.material;
        lDiffuse = mat.kd * coeff;


        Vector<double> v1(nearestTriangle.p1, nearestTriangle.p2);
        Vector<double> v3(nearestTriangle.p1, nearestTriangle.p3);
        Vector<double> N = (v1^v3).normalizeVector();
        Vector<double> L(pIntersection, light);

        // ambient light :
        lAmbient = double(INTENSITY) * mat.ka;

        // specular light
        Vector<double>V(pIntersection, origin);
        Vector<double> R = (N *((N * L.normalizeVector()) * 2) ) - L.normalizeVector();
        lSpeculaire = mat.ks * double(INTENSITY) * pow(max(0.,R * V.normalizeVector()), mat.ns);


        // compute shadows
        Ray rayShadow(pIntersection + Point(0.01*N.vx, 0.01*N.vy, 0.01*N.vz), L.normalizeVector());
        Point pIntersectionShadow;
        int idNearestTriangleShadow = -1;
        bool intersection_shadow = r.computeIntersections(rayShadow, pIntersectionShadow, idNearestTriangleShadow);
        Triangle nearestTriangleShadow = SceneReader::allTriangles[idNearestTriangleShadow];
        if(intersection_shadow && nearestTriangle.meshId != nearestTriangleShadow.meshId) {
            Vector<double> vSourceShadow(pIntersection, pIntersectionShadow);
            if (vSourceShadow.getNorm() < L.getNorm()) {
                lDiffuse = Vector<double>(0, 0, 0);
                lAmbient = Vector<double>(0, 0, 0);
                lSpeculaire = Vector<double>(0, 0, 0);
            }
        }

    }
    if(lDiffuse.vx < 0 || lDiffuse.vy < 0 || lDiffuse.vz < 0)
        return Vector<double>(0,0,0);

    return lDiffuse + lAmbient + lSpeculaire;
}