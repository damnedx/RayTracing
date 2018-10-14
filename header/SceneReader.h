//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_SCENEREADER_H
#define RAYTRACING_SCENEREADER_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
// C++ template to print vector container elements
template <typename T>
inline ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[ ";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", " << endl;
    }
    os << " ]\n";
    return os;
}

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
