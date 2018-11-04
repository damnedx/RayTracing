//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_IMAGEWRITER_H
#define RAYTRACING_IMAGEWRITER_H
#include <iostream>
using namespace std;

class ImageWriter {

public:
    ImageWriter() = delete;
    ~ImageWriter() = default;

    static void saveImage(string filename, int image[], int width, int height);

};


#endif //RAYTRACING_IMAGEWRITER_H
