//
// Created by Home on 02/11/2018.
//

#include "../header/Ray.h"
#include "../header/SceneReader.h"
#include "../header/Grid.h"

#define INTENSITY 10000
int Ray::compute_intersection_1;
int Ray::compute_intersection_2;

Ray::Ray(const Point& O, const Vector<double>& dir) {

    this->pSource = O;
    this->dir = dir;

}

Point Ray::ray_position(double t) const {
    Vector<double> proj = t * this->dir;
    return this->pSource + Point(proj.vx, proj.vy, proj.vz);
}

bool Ray::intersectTriangle(const Triangle& t, Point& pIntersection, float &distance) const {

    compute_intersection_1++;
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
        distance = p;
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
    vector<Triangle> v = Grid::getTrianglesDDA(r);
    float hit;
    for (auto& t : v) {
        bool intersection = r.intersectTriangle(t, pIntersection, hit);
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
bool Ray::computeIntersections2(Ray &r, vector<Triangle> triangles, float &distance, int &triangleId) const {

    compute_intersection_2++;
    bool has_intersection = false;
    distance = MAXFLOAT;
    Vector<float> minDistanceOriginTriangle(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    for (auto& t : triangles) {
        Point pIntersection;
        float hit = 0;
        bool intersection = r.intersectTriangle(t, pIntersection, hit);
        if(intersection){
            has_intersection = true;
            if(hit < distance){
                distance = hit;
                triangleId = t.id;
            }
        }
    }
    return has_intersection;
}

bool Ray::intersectBbox(Bbox &b, Vector<double> &invDir, Vector<double> &sign, float &tHit) {

    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    tmin  = (b[sign[0]].x - pSource.x) * invDir.vx;
    tmax  = (b[1 - sign[0]].x - pSource.x) * invDir.vx;
    tymin = (b[sign[1]    ].y - pSource.y) * invDir.vy;
    tymax = (b[1 - sign[1]].y - pSource.y) * invDir.vy;

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (b[sign[2]    ].z - pSource.z) * invDir.vz;
    tzmax = (b[1 - sign[2]].z - pSource.z) * invDir.vz;

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    tHit = tmin;

    return true;
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
        lDiffuse = Vector<double>(0,0,0);

    if(lAmbient.vx < 0 || lAmbient.vy < 0 || lAmbient.vz < 0)
        lAmbient = Vector<double>(0,0,0);

    if(lSpeculaire.vx < 0 || lSpeculaire.vy < 0 || lSpeculaire.vz < 0)
        lSpeculaire = Vector<double>(0,0,0);

    return lDiffuse + lAmbient + lSpeculaire;
}