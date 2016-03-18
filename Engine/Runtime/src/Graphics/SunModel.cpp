// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunModel.h"

GLint textureFromFile(const char *path, string directory) {
    string filename = directory + string(path);

    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image);

    return textureID;
}

SunModel::SunModel(string _file, bool _flipNormals) {
	// Import the mesh data
    importMeshData(_file, _flipNormals);
}

void SunModel::init() {
    
}

void SunModel::importMeshData(string _file, bool _flipNormals) {
	((SunLogger *)getService("logger"))->log("Attempting to load model " + _file);
    // Set Flip Normals
    flipNormals = _flipNormals;

    // Create an importer and import the file
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(_file, aiProcess_GenNormals | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    // Set the directory variable
    this->directory = _file.substr(0, _file.find_last_of('/'));

    // Root node of the scene
    aiNode *node = scene->mRootNode;
    // Process the root node
    processMeshNode(node, scene);
	((SunLogger *)getService("logger"))->logSuccess("Loaded model " + _file);
}

void SunModel::render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material, SunMeshRenderType _renderType) {
    // Loop through sub-meshes and render
    for (int i = 0; i < meshes.size(); i++)
        meshes[i].render(_shader, _deltaTime, _position, _rotation, _scale, _material, _renderType);
}

void SunModel::processMeshNode(aiNode *_node, const aiScene *_scene) {
    // Loop through meshes
    for (int i = 0; i < _node->mNumMeshes; i++) {
        // Mesh at [i] of the node
        aiMesh *mesh = _scene->mMeshes[_node->mMeshes[i]];

        // Add processed mesh to the mesh list
        meshes.push_back(processMeshData(mesh, _scene));
    }

    // Loop through sub-nodes
    for (int i = 0; i < _node->mNumChildren; i++) {
        // Process sub-nodes
        processMeshNode(_node->mChildren[i], _scene);
    }
}

void SunModel::processMeshNodeForBones(aiNode* _node, const aiScene* _scene) {
    for (int i = 0; i < boneNames.size(); i++) {
        if (_node->mName.C_Str() == boneNames[i]) {
            bones[i].parentID = -1;
            aiMatrix4x4 m = assimpBones[i]->mOffsetMatrix;
            glm::mat4 offsetMatrix = glm::mat4(m.a1, m.a2, m.a3, m.a4, m.b1, m.b2, m.b3, m.b4, m.c1, m.c2, m.c3, m.c4, m.d1, m.d2, m.d3, m.d4);
            //bones[i].relativeTransform = offsetMatrix;
            bones[i].inverseBindPose = offsetMatrix;
            for (int j = 0; j < boneNames.size(); j++) {
                if (boneNames[j] == _node->mParent->mName.C_Str()) {
                    int position = find(boneNames.begin(), boneNames.end(), _node->mParent->mName.C_Str()) - boneNames.begin();
                    bones[i].parentID = position;
                }
            }
        }
    }

    // Loop through sub-nodes
    for (int i = 0; i < _node->mNumChildren; i++) {
        // Process sub-nodes
        processMeshNodeForBones(_node->mChildren[i], _scene);
    }
}

SunMesh SunModel::processMeshData(aiMesh* _mesh, const aiScene* _scene) {
    // Vertices, Indices, and Textures
    vector<SunVertex> vertices;
    vector<GLuint> indices;
    vector<SunTexture> textures;
    map<string, SunBone> boneMap;
    vector<SunAnimation> animations;

    for (int i = 0; i < _mesh->mNumBones; i++) {
        string boneName = _mesh->mBones[i]->mName.C_Str();
        assimpBones.push_back(_mesh->mBones[i]);

        boneNames.push_back(boneName);

        SunBone bone;
        bone.name = boneName;
        bone.parentID = -1;

        boneMap[boneName] = bone;
        bones.push_back(bone);
    }

    processMeshNodeForBones(_scene->mRootNode, _scene);

    // Loop through the vertices of the mesh
    for (int i = 0; i < _mesh->mNumVertices; i++) {
        // Create vertex object
        SunVertex vertex;

        // Position
        glm::vec3 position;

        // Set the position's x, y, and z from the mesh data
        position.x = _mesh->mVertices[i].x;
        position.y = _mesh->mVertices[i].y;
        position.z = _mesh->mVertices[i].z;

        // Normal
        glm::vec3 normal;

        // Set the position's normal's x, y, and z from the mesh data
        normal.x = _mesh->mNormals[i].x;
        normal.y = _mesh->mNormals[i].y;
        normal.z = _mesh->mNormals[i].z;

        if (flipNormals) {
            normal = -normal;
		}

        // Tangent
        glm::vec3 tangent = glm::vec3(0.0, 0.0, 0.0);

        // Texture Coordinates
        glm::vec2 textureCoordinates = glm::vec2(0.0, 0.0);

        // Check for texture coordinates
        if (_mesh->mTextureCoords[0]) {
            // Set the texture coordinates' x and y from the mesh data
            textureCoordinates.x = _mesh->mTextureCoords[0][i].x;
            textureCoordinates.y = _mesh->mTextureCoords[0][i].y;

            // Set the position's tangent's x, y, and z from the mesh data
            tangent.x = _mesh->mTangents[i].x;
            tangent.y = _mesh->mTangents[i].y;
            tangent.z = _mesh->mTangents[i].z;
        }

        // Assign the position, normal, and texture coordinates to the vertex
        vertex.position = position;
        vertex.normal = normal;
        vertex.tangent = tangent;
        vertex.textureCoordinates = textureCoordinates;

        vertex.boneIDs[0] = 0;
        vertex.boneIDs[1] = 1;
        vertex.boneIDs[2] = 2;
        vertex.boneIDs[3] = 3;

        vertex.boneWeights[0] = 0;
        vertex.boneWeights[1] = 0;
        vertex.boneWeights[2] = 0;
        vertex.boneWeights[3] = 0;
        // Add the vertex to the mesh's list of vertices
        vertices.push_back(vertex);
    }

    for (int i = 0; i < _mesh->mNumBones; i++) {
        for (int j = 0; j < _mesh->mBones[i]->mNumWeights; j++) {
            vertices[_mesh->mBones[i]->mWeights[j].mVertexId].boneIDs[i] = i;
            vertices[_mesh->mBones[i]->mWeights[j].mVertexId].boneWeights[i] = _mesh->mBones[i]->mWeights[j].mWeight;
        }
    }

    for (int i = 0; i < _scene->mNumAnimations; i++) {
        SunAnimation animation;

        animation.ticksPerSecond = 30;
        animation.length = _scene->mAnimations[i]->mDuration;

        for (int j = 0; j < _scene->mAnimations[i]->mNumChannels; j++) {
            SunAnimationChannel channel;

            int position = find(boneNames.begin(), boneNames.end(), _scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str()) - boneNames.begin();
            channel.boneID = position;

            for (int k = 0; k < _scene->mAnimations[i]->mChannels[j]->mNumRotationKeys; k++) {
                aiQuaternion quaternion = _scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mValue;
                glm::quat rotation = glm::quat(quaternion.w, quaternion.x, quaternion.y, quaternion.z);

                channel.rotationKeyTicks.push_back(_scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mTime * animation.ticksPerSecond);
                channel.rotationKeyValues.push_back(rotation);
            }

            animation.channels.push_back(channel);
        }

        animations.push_back(animation);
    }

    // Loop throught the faces of the mesh (Triangles)
    for (int i = 0; i < _mesh->mNumFaces; i++) {
        // Face
        aiFace face = _mesh->mFaces[i];

        // Loop through the indices of the face
        for (int j = 0; j < face.mNumIndices; j++) {
            // Add the indices to the mesh's list of indices
            indices.push_back(face.mIndices[j]);
        }
    }

    // Check for materials
    if (_scene->HasMaterials()) {
        // Load the material
        aiMaterial *material = _scene->mMaterials[_mesh->mMaterialIndex];

        // Load the diffuse textures
        vector<SunTexture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
        // Add the diffuse textures to the mesh's list of textures
       	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Load the specular textures
        vector<SunTexture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
        // Add the specular textures to the mesh's list of textures
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // Load the normal textures
        vector<SunTexture> normalMaps = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
        // Add the normal textures to the mesh's list of textures
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    }

    SunMesh mesh = SunMesh(vertices, indices, textures, bones, animations);

    aiMatrix4x4 m = _scene->mRootNode->mTransformation;
    mesh.setGlobalInverseTransform(glm::inverse(glm::mat4(m.a1, m.a2, m.a3, m.a4, m.b1, m.b2, m.b3, m.b4, m.c1, m.c2, m.c3, m.c4, m.d1, m.d2, m.d3, m.d4)));

    return mesh;
}

vector<SunTexture> SunModel::loadMaterialTextures(aiMaterial* _material, aiTextureType _type, string _typeName) {
    vector<SunTexture> textures;
    for (int i = 0; i < _material->GetTextureCount(_type); i++) {
        aiString string;
        _material->GetTexture(_type, i, &string);
        GLboolean skip = false;
        for (GLuint j = 0; j < loadedTextures.size(); j++) {
            if (loadedTextures[j].path == string) {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            SunTexture texture;
            texture.id = textureFromFile(string.C_Str(), directory);
            texture.path = string;
            textures.push_back(texture);
            this->loadedTextures.push_back(texture);
        }
    }

    return textures;
}
