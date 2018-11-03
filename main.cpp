#include <iostream>
#include "header/SceneReader.h"
#include "header/Point.h"
#include "header/Ray.h"
#include <cmath>

#define PI 3.14159265

int main() {
    SceneReader sc("../data/scene");

    Point origin(0,0,0);

    float fov = (60 * PI)/180;

    for(int i = 0; i < sc.height; i++){
        for(int j = 0; j < sc.width; j++){
            Vector<float> dir(j - sc.width/2, i - sc.height/2, - sc.width/(2*tan(fov/2)));
            Ray r(origin, dir);

        }
    }

    return 0;
}