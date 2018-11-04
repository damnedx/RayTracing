//
// Created by Home on 03/11/2018.
//

#include "../header/ImageWriter.h"
#include "../header/Logger.h"
#include <fstream>


void ImageWriter::saveImage(string filename, int image[], int width, int height) {
    ofstream f(filename);

    // write header ppm
    f << "P3\r\n" ;
    f << width << " " <<height <<  "\r\n";
    f << "255\r\n";

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            f << image[(j * width + i) * 3 + 1]  << " ";
            f << image[(j * width + i) * 3 + 2]  << " ";
            f << image[(j * width + i) * 3 + 3]  << "\r\n";
        }
    }

    f.close();

    Logger::InfoMessage("Image saved !");


}

