// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNMESH_H
#define SUNMESH_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "SunPrimitives.h"
#include "SunShader.h"

// SunObjectMaterial Declaration
struct SunObjectMaterial {
	SunObjectMaterial() {

	}
	SunObjectMaterial(glm::vec3 _color, GLfloat _shininess) {
		color = _color;
		shininess = _shininess;
	}
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

    SunMesh(std::vector<SunVertex> _vertices, std::vector<GLuint> _indices, std::vector<SunTexture> _textures, std::vector<SunBone> _bones, std::vector<SunAnimation> _animations);

    void setUpGL();
    void calculateBindPoseAndInverseBindPose();
    void calculateBoneGlobalTransforms(GLfloat _currentTick);
    void passGlobalTransformUniforms(SunShader _shader);
    void render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material, SunMeshRenderType _renderType);

    inline std::vector<SunVertex> & getVertices() { return vertices; }
    inline SunVertex & getVertexAtIndex(int i) { return vertices[i]; }
    inline void addVertexToVertices(SunVertex vertex) { vertices.push_back(vertex); }

    inline std::vector<GLuint> & getIndices() { return indices; }
    inline GLuint & getIndexAtIndex(int i) { return indices[i]; }
    inline void addIndexToIndices(GLuint index) { indices.push_back(index); }

    inline std::vector<SunTexture> & getTextures() { return textures; }
    inline SunTexture & getTextureAtIndex(int i) { return textures[i]; }
    inline void addTextureToTextures(SunTexture texture) { textures.push_back(texture); }

    inline std::vector<SunBone> & getBones() { return bones; }
    inline SunBone & getBoneAtIndex(int i) { return bones[i]; }
    inline void addBoneToBones(SunBone bone) { bones.push_back(bone); }

    inline std::vector<SunAnimation> & getAnimations() { return animations; }
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
    std::vector<SunVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<SunTexture> textures;
    std::vector<SunBone> bones;
    std::vector<SunAnimation> animations;

    // Global Inverse Transform
    glm::mat4 globalInverseTransform;

    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
};

#endif
