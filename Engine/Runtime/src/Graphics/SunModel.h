// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_SunModel_h
#define OpenGL_Test_3_SunModel_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL/SOIL.h>

#include "../Core/SunBase.h"
#include "../Output/SunLogger.h"
#include "SunMesh.h"

extern GLint textureFromFile(const char *path, string directory);

class SunModel : public SunBase {
public:
    SunModel() { }
    SunModel(string _file, bool _flipNormals);

    void importMeshData(string _file, bool _flipNormals);
    void render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material, SunMeshRenderType _renderType);

    inline vector<SunMesh> & getMeshes() { return meshes; }
    inline SunMesh & getMeshAtIndex(int i) { return meshes[i]; }
    inline void addMesh(SunMesh mesh) { meshes.push_back(mesh); }

    inline bool & getFlipNormals() { return flipNormals; }
    inline void setFlipNormals(bool _f) { flipNormals = _f; }
private:
    // Textures
    vector<SunTexture> loadedTextures;
    vector<string> boneNames;
    vector<SunBone> bones;
    vector<const aiBone *> assimpBones;

    // Meshes attached to the model
    vector<SunMesh> meshes;
    // Directory of the file
    string directory;

    // Flip Normals (quick hack) REMOVE LATER, QUICK HACK
    bool flipNormals;

    void processMeshNode(aiNode *_node, const aiScene *_scene);
    void processMeshNodeForBones(aiNode *_node, const aiScene *_scene);
    SunMesh processMeshData(aiMesh *_mesh, const aiScene *_scene);
    vector<SunTexture> loadMaterialTextures(aiMaterial *_material, aiTextureType _type, string _typeName);
};

#endif
