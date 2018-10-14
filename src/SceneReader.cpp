//
// Created by Home on 14/10/2018.
//

#include <vector>
#include<iterator>

#include "../header/SceneReader.h"
#include "../header/Logger.h"
#include "../header/Material.h"
#include "../header/Triangle.h"
#include "../header/Point.h"

// C++ template to print vector container elements
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
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

SceneReader::SceneReader(string filename) {

    ifstream fileScene(filename);
    if (!fileScene){
        Logger::ErrorMessage("No file scene found !");
        exit(1);
    }

    // read size
    fileScene >> this->_width >> this->_height;
    fileScene >> this->_materialSize >> this->_triangleSize;

    vector<Material> allMaterials;
    // materials load
    for(auto i = 0; i < this->_materialSize; i++){
        float r,g,b,reflection;
        fileScene >> r  >> g >> b >> reflection;
        allMaterials.emplace_back(Material(r,g,b,reflection));
    }

    vector<Triangle> allTriangles;
    // triangles load
    for(auto i = 0; i < this->_triangleSize; i++){

        float xA,yA,zA;
        float xB,yB,zB;
        float xC,yC,zC;
        unsigned int materialId;

        fileScene >> xA  >> yA >> zA >>  xB  >> yB >> zB >>  xC  >> yC >> zC >> materialId;

        if(materialId >= this->_materialSize){
            Logger::ErrorMessage("Material not found for triangle : " + to_string(i));
            exit(1);
        }
        allTriangles.emplace_back(
                Triangle(
                        Point(xA, yA, zA),
                        Point(xB, yB, zB),
                        Point(xC, yC, zC),
                        materialId));

    }

    cout << allMaterials << endl;
    cout << allTriangles << endl;





    fileScene.close();
}



ostream& operator<<(ostream& os, const SceneReader& dt)
{
    return os;
}
