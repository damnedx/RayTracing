#include <iostream>
#include "header/SceneReader.h"
#include "header/Point.h"
#include "header/Ray.h"
#include "header/ImageWriter.h"
#include <cmath>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std::chrono;

#define PI 3.14159265
#define FOV 60

int main() {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    SceneReader sc("../data/scene");

    Point origin(0, 0, 20);

    float fov = (FOV * PI) / 180;

    int *image = new int[sc.height * sc.width * 3];

    Point light(0,0, 20);


#pragma omp parallel for
    for (int i = 0; i < sc.height; i++) {
        for (int j = 0; j < sc.width; j++) {
            float u = float(i) / float(sc.width);
            float v = float(j) / float(sc.height);

            Vector<double> dir(j - sc.width / 2, i - sc.height / 2, -sc.width / (2 * tan(fov / 2)));
            Ray r(origin, dir.normalizeVector());
            int idNearestTriangle = -1;
            Vector<double> luminosity = r.computeLuminosityAtPoint(r, light, origin, idNearestTriangle);

            image[((sc.height - i - 1) * sc.width + j) * 3 + 0] = min(255.0f, float(pow(luminosity.vx, 1/2.2)));
            image[((sc.height - i - 1) * sc.width + j) * 3 + 1] = min(255.0f, float(pow(luminosity.vy, 1/2.2)));
            image[((sc.height - i - 1) * sc.width + j) * 3 + 2] = min(255.0f, float(pow(luminosity.vz, 1/2.2)));



        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout << "Total time : " << duration << " s" << endl;

    ImageWriter::saveImage("test.ppm", image, sc.width, sc.height);
    delete[] image;


}