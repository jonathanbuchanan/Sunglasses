//
//  SunModel.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/13/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

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
#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"

#include "../Libraries/assimp/Importer.hpp"
#include "../Libraries/assimp/scene.h"
#include "../Libraries/assimp/postprocess.h"

#include "../Libraries/SOIL/SOIL.h"

#include "./SunMesh.h"

extern GLint textureFromFile(const char *path, string directory);

class SunModel {
public:
    SunModel() { }
    SunModel(string _file);
    
    void importMeshData(string _file);
    void render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material, SunMeshRenderType _renderType);
    
    inline vector<SunMesh> & getMeshes() { return meshes; }
    inline SunMesh & getMeshAtIndex(int i) { return meshes[i]; }
    inline void addMesh(SunMesh mesh) { meshes.push_back(mesh); }
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
    
    void processMeshNode(aiNode *_node, const aiScene *_scene);
    void processMeshNodeForBones(aiNode *_node, const aiScene *_scene);
    SunMesh processMeshData(aiMesh *_mesh, const aiScene *_scene);
    vector<SunTexture> loadMaterialTextures(aiMaterial *_material, aiTextureType _type, string _typeName);
};

#endif
