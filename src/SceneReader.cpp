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
#include "../header/Vector.h"
#include "../header/Ray.h"

SceneReader::SceneReader(string filename) {

    Logger::InfoMessage("Reading scene file...");
    ifstream fileScene(filename);
    if (!fileScene){
        Logger::ErrorMessage("No file scene found !");
        exit(1);
    }

    // read size
    fileScene >> this->width >> this->height;
    fileScene >> this->_materialSize >> this->_triangleSize;

    vector<Material> allMaterials;
    // materials load
    for(auto i = 0; i < this->_materialSize; i++){
        float r,g,b,reflection;
        fileScene >> r  >> g >> b >> reflection;
        this->allMaterials.emplace_back(Material(r,g,b,reflection));
    }

    Logger::InfoMessage(to_string(this->_materialSize) + " material(s) loaded");

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
        this->allTriangles.emplace_back(
                Triangle(
                        Point(xA, yA, zA),
                        Point(xB, yB, zB),
                        Point(xC, yC, zC),
                        materialId));

    }
    Logger::InfoMessage(to_string(this->_triangleSize) + " triangle(s) loaded");

    cout << allMaterials << endl;
    cout << allTriangles << endl;

    Logger::InfoMessage("Scene data loaded!");
    fileScene.close();

}



ostream& operator<<(ostream& os, const SceneReader& dt)
{
    return os;
}
