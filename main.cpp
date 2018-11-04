#include <iostream>
#include "header/SceneReader.h"
#include "header/Point.h"
#include "header/Ray.h"
#include "header/ImageWriter.h"
#include <cmath>

#define PI 3.14159265
#define FOV 60

int main() {
    SceneReader sc("../data/scene");

    Point origin(0,0,0);

    float fov = (FOV * PI)/180;

    int* image = new int[sc.height * sc.width * 3];

    for(int i = 0; i < sc.height; i++){
        for(int j = 0; j < sc.width; j++){
            Vector<float> dir(j - sc.width/2, i - sc.height/2, - sc.width/(2*tan(fov/2)));

            float norm = sqrt(dir.vx * dir.vx + dir.vy * dir.vy + dir.vz * dir.vz);
            Vector<float> dirNorm(dir.vx / norm, dir.vy / norm, dir.vz / norm);
            Ray r(origin, dirNorm);

            bool intersection = r.intersectTriangle(sc.allTriangles[0]);

            image[(i * sc.width + j) * 3 + 1] = intersection ? 255 : 0;
            image[(i * sc.width + j) * 3 + 0] = intersection ? 255 : 0;
            image[(i * sc.width + j) * 3 + 2] = intersection ? 255 : 0;
        }
    }
    ImageWriter::saveImage("test.ppm", image, sc.width, sc.height);
    delete[] image;


}