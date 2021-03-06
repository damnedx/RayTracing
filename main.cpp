#include <iostream>
#include "header/SceneReader.h"
#include "header/Point.h"
#include "header/Ray.h"
#include "header/ImageWriter.h"
#include <cmath>
#include <algorithm>
#include <omp.h>
#include <chrono>
#include "header/Grid.h"
#include "header/Logger.h"

using namespace std::chrono;

#define PI 3.14159265
#define FOV 60
#define PIXEL_SAMPLING 4
int main() {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    SceneReader sc("../data/scene");

    Point origin(0, 0, 20);

    float fov = (FOV * PI) / 180;

    int *image = new int[sc.height * sc.width * 3];

    Point light(7,0, 20);

    // init Grid
    Grid g(SceneReader::allTriangles);
    Logger::InfoMessage("Acceleration grid loaded!");

#pragma omp parallel for
    for (int i = 0; i < sc.height; i++) {
        for (int j = 0; j < sc.width; j++) {
            float u = float(i) / float(sc.width);
            float v = float(j) / float(sc.height);
            Vector<double> luminosity(0,0,0);
            vector<Point> stochastic_sampling = Ray::generate_stochastic_sampling(PIXEL_SAMPLING);
            for(auto& v : stochastic_sampling){
                Vector<double> dir(j - sc.width / 2, i - sc.height / 2, -sc.width / (2 * tan(fov / 2)));
                dir = dir + Vector<double>(v.x, v.y, v.z);
                Ray r(origin, dir.normalizeVector());
                int idNearestTriangle = -1;
                luminosity = luminosity + r.computeLuminosityAtPoint(r, light, origin, idNearestTriangle);
            }
            luminosity = luminosity / (double(PIXEL_SAMPLING) * double(PIXEL_SAMPLING));


            image[((sc.height - i - 1) * sc.width + j) * 3 + 0] = min(255.0f, float(pow(luminosity.vx, 1/2.2)));
            image[((sc.height - i - 1) * sc.width + j) * 3 + 1] = min(255.0f, float(pow(luminosity.vy, 1/2.2)));
            image[((sc.height - i - 1) * sc.width + j) * 3 + 2] = min(255.0f, float(pow(luminosity.vz, 1/2.2)));



        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout << "Total time : " << duration << " s" << endl;
    cout << "Total ray intersections computations : " << Ray::compute_intersection_1 + Ray::compute_intersection_2 << endl;

    ImageWriter::saveImage("test.ppm", image, sc.width, sc.height);
    delete[] image;


}