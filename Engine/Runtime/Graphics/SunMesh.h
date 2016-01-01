// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_SunMesh_h
#define OpenGL_Test_3_SunMesh_h

#include <vector>
using namespace std;

#include <GL/glew.h>
#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/gtc/quaternion.hpp"
#include "../Libraries/glm/gtc/type_ptr.hpp"
#include "../Libraries/glm/gtx/quaternion.hpp"
#include "../Libraries/glm/gtx/string_cast.hpp"

#include "./SunPrimitives.h"
#include "./Shaders/SunShader.h"

// SunObjectMaterial Declaration
struct SunObjectMaterial {
    glm::vec3 color;
    GLfloat shininess;
};

// SunMeshRenderType Declaration
enum SunMeshRenderType {
    SunMeshRenderTypeSolid,
    SunMeshRenderTypeTextured,
	SunMeshRenderTypeAll
};

class SunMesh {
public:
    SunMesh() { }
    
    SunMesh(vector<SunVertex> _vertices, vector<GLuint> _indices, vector<SunTexture> _textures, vector<SunBone> _bones, vector<SunAnimation> _animations);
    
    void setUpGL();
    void calculateBindPoseAndInverseBindPose();
    void calculateBoneGlobalTransforms(GLfloat _currentTick);
    void passGlobalTransformUniforms(SunShader _shader);
    void render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material, SunMeshRenderType _renderType);
    
    inline vector<SunVertex> & getVertices() { return vertices; }
    inline SunVertex & getVertexAtIndex(int i) { return vertices[i]; }
    inline void addVertexToVertices(SunVertex vertex) { vertices.push_back(vertex); }
    
    inline vector<GLuint> & getIndices() { return indices; }
    inline GLuint & getIndexAtIndex(int i) { return indices[i]; }
    inline void addIndexToIndices(GLuint index) { indices.push_back(index); }
    
    inline vector<SunTexture> & getTextures() { return textures; }
    inline SunTexture & getTextureAtIndex(int i) { return textures[i]; }
    inline void addTextureToTextures(SunTexture texture) { textures.push_back(texture); }
    
    inline vector<SunBone> & getBones() { return bones; }
    inline SunBone & getBoneAtIndex(int i) { return bones[i]; }
    inline void addBoneToBones(SunBone bone) { bones.push_back(bone); }
    
    inline vector<SunAnimation> & getAnimations() { return animations; }
    inline SunAnimation & getAnimationAtIndex(int i) { return animations[i]; }
    inline void addAnimationToAnimations(SunAnimation animation) { animations.push_back(animation); }
    
    inline glm::mat4 & getGlobalInverseTransform() { return globalInverseTransform; }
    inline void setGlobalInverseTransform(glm::mat4 _transform) { globalInverseTransform = _transform; }
    
    inline GLuint & getVBO() { return VBO; }
    inline void setVBO(GLuint _VBO) { VBO = _VBO; }
    
    inline GLuint & getVAO() { return VAO; }
    inline void setVAO(GLuint _VAO) { VAO = _VAO; }
    
    inline GLuint & getEBO() { return EBO; }
    inline void setEBO(GLuint _EBO) { EBO = _EBO; }
private:
    // Vertices, indices, and textures
    vector<SunVertex> vertices;
    vector<GLuint> indices;
    vector<SunTexture> textures;
    vector<SunBone> bones;
    vector<SunAnimation> animations;
    
    // Global Inverse Transform
    glm::mat4 globalInverseTransform;

    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
};

#endif