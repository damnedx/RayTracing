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
#include "../header/OBJ_Loader.h"

#define SCALING_FACTOR 1
vector<Triangle> SceneReader::allTriangles;
vector<Material> SceneReader::allMaterials;

SceneReader::SceneReader(string filename) {

    Logger::InfoMessage("Reading scene file...");

    this->width = 640;
    this->height = 480;

    vector<Material> allMaterials;

    // Initialize Loader
    objl::Loader Loader;
    bool loadout = Loader.LoadFile("../data/scene.obj");
    if (loadout)
    {
        int id = 0;
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
            objl::Mesh curMesh = Loader.LoadedMeshes[i];
            for (int j = 0; j < curMesh.Vertices.size(); j += 3)
            {
                Triangle t = Triangle(
                        Point(curMesh.Vertices[j].Position.X * SCALING_FACTOR,curMesh.Vertices[j].Position.Z * SCALING_FACTOR,
                              curMesh.Vertices[j].Position.Y * SCALING_FACTOR),
                        Point(curMesh.Vertices[j+1].Position.X * SCALING_FACTOR,curMesh.Vertices[j+1].Position.Z * SCALING_FACTOR,
                              curMesh.Vertices[j+1].Position.Y * SCALING_FACTOR),
                        Point(curMesh.Vertices[j+2].Position.X * SCALING_FACTOR,curMesh.Vertices[j+2].Position.Z * SCALING_FACTOR,
                              curMesh.Vertices[j+2].Position.Y * SCALING_FACTOR),
                        id);

                t.setNormal(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z);
                Material m;
                m.setMaterial(Vector<double>(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z),
                        Vector<double>(curMesh.MeshMaterial.Kd.X,curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z),
                        Vector<double>(curMesh.MeshMaterial.Ka.X,curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z),
                        curMesh.MeshMaterial.Ns);
                t.material = m;
                t.meshId = i;
                this->allTriangles.emplace_back(t);

                id = id + 1;
            }
        }
    } else{
        Logger::ErrorMessage("Cannot load the mesh");
        exit(1);
    }

    Logger::InfoMessage(to_string(this->allTriangles.size()) + " triangle(s) loaded");
    Logger::InfoMessage("Scene data loaded!");

}

ostream& operator<<(ostream& os, const SceneReader& dt)
{
    return os;
}
