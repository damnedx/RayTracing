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
            int idNearestTriangle;

            float luminosity = r.computeLuminosityAtPoint(r, light, idNearestTriangle);

            Triangle t = SceneReader::allTriangles[idNearestTriangle];

            if(luminosity >= 0){
                image[((sc.height - i - 1) * sc.width + j) * 3 + 0] = min(255.0f, float(pow(sc.allMaterials[t.materialId].r * luminosity, 1/2.2)));
                image[((sc.height - i - 1) * sc.width + j) * 3 + 1] = min(255.0f, float(pow(sc.allMaterials[t.materialId].g * luminosity, 1/2.2)));
                image[((sc.height - i - 1) * sc.width + j) * 3 + 2] = min(255.0f, float(pow(sc.allMaterials[t.materialId].b * luminosity, 1/2.2)));
            }

        }
    }
    ImageWriter::saveImage("test.ppm", image, sc.width, sc.height);
    delete[] image;


}