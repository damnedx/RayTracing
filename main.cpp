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

    Point light(0, -sc.height / 2, -500);

    for (int i = 0; i < sc.height; i++) {
        for (int j = 0; j < sc.width; j++) {
            Vector<float> dir(j - sc.width / 2, i - sc.height / 2, -sc.width / (2 * tan(fov / 2)));
            Ray r(origin, dir.normalizeVector());
            for (auto t = sc.allTriangles.begin(); t < sc.allTriangles.end(); t++) {
                Point p;
                bool intersection = r.intersectTriangle(*t, p);
                if (intersection) {
                    float luminosity = r.lightAtPoint(p, light, *t);
                    // check shadow
                    // look if there is an obstacle between the current point and the source light
                    Point pIntersectionObstacle;

                    Ray ray_shadow(p, Vector<float>(p, light));

                    bool intersection_obstacle = ray_shadow.intersectTriangle(*t, pIntersectionObstacle);
                    Vector<float> vSourceObstacle(p, pIntersectionObstacle);
                    if(intersection_obstacle && (vSourceObstacle.getNorm() < Vector<float>(p, light).getNorm())){
                        luminosity = 0;
                    }

                    if (luminosity > 0) {
                        image[(i * sc.width + j) * 3 + 0] = min(255.0f, sc.allMaterials[t->materialId].r * luminosity);
                        image[(i * sc.width + j) * 3 + 1] = min(255.0f, sc.allMaterials[t->materialId].g * luminosity);
                        image[(i * sc.width + j) * 3 + 2] = min(255.0f, sc.allMaterials[t->materialId].b * luminosity);
                    }

                }
            }


        }
    }
    ImageWriter::saveImage("test.ppm", image, sc.width, sc.height);
    delete[] image;


}