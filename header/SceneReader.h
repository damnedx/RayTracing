//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_SCENEREADER_H
#define RAYTRACING_SCENEREADER_H

#include <iostream>
#include <fstream>
using namespace std;

class SceneReader {
private:
    unsigned int _height;
    unsigned int _width;
    unsigned int _materialSize;
    unsigned int _triangleSize;


public:
    SceneReader() = default;
    SceneReader(string filename);
    ~SceneReader() = default;
    friend ostream& operator<<(ostream& os, const SceneReader& sr);
};


#endif //RAYTRACING_SCENEREADER_H
