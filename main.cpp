#include <iostream>
#include "header/SceneReader.h"
#include "header/Point.h"
#include "header/Ray.h"
#include "header/ImageWriter.h"
#include <cmath>
#include <algorithm>

#define PI 3.14159265
#define FOV 60

int main() {
    SceneReader sc("../data/scene");

    Point origin(0, 0, 0);

    float fov = (FOV * PI) / 180;

    int *image = new int[sc.height * sc.width * 3];

    Point light(150, sc.height / 2, -450);

    for (int i = 0; i < sc.height; i++) {
        for (int j = 0; j < sc.width; j++) {
            Vector<float> dir(j - sc.width / 2, i - sc.height / 2, -sc.width / (2 * tan(fov / 2)));
            Ray r(origin, dir.normalizeVector());
            Point pIntersection;

            unsigned int idNearestTriangle;

            bool intersection = sc.computeIntersections(r, pIntersection, idNearestTriangle);

            if (intersection) {
                Triangle t = sc.allTriangles[idNearestTriangle];
                float luminosity = r.lightAtPoint(pIntersection, light, t);
                Vector<float> v1(t.p1, t.p2);
                Vector<float> v3(t.p1, t.p3);
                Vector<float> normal = (v1^v3).normalizeVector();
                // compute shadows
                Vector<float> vTriangleLight(pIntersection, light);
                Ray rayShadow(Point(pIntersection.x + normal.vx,pIntersection.y + normal.vy,pIntersection.z + normal.vz) , vTriangleLight.normalizeVector());
                Point pIntersectionShadow;
                unsigned int idNearestTriangleShadow;
                bool intersection_shadow = sc.computeIntersections(rayShadow, pIntersectionShadow, idNearestTriangleShadow);
                if(intersection_shadow){
                    Vector<float> vSourceShadow(pIntersection, pIntersectionShadow);
                    if(vSourceShadow.getNorm() < vTriangleLight.getNorm())
                        luminosity = 0;
                }
                if(luminosity >= 0){
                    image[((sc.height - i - 1) * sc.width + j) * 3 + 0] = min(255.0f, sc.allMaterials[t.materialId].r * luminosity);
                    image[((sc.height - i - 1) * sc.width + j) * 3 + 1] = min(255.0f, sc.allMaterials[t.materialId].g * luminosity);
                    image[((sc.height - i - 1) * sc.width + j) * 3 + 2] = min(255.0f, sc.allMaterials[t.materialId].b * luminosity);
                }
            }

        }
    }
    ImageWriter::saveImage("test.ppm", image, sc.width, sc.height);
    delete[] image;


}