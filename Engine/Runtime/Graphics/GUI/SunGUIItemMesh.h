// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunGUIItemMesh_h
#define Sunglasses_SunGUIItemMesh_h

#include <vector>
using namespace std;

#include <GL/glew.h>
#include "../Shaders/SunShader.h"
#include "../SunTextRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <SOIL/SOIL.h>

struct SunBasicVertex {
    glm::vec2 position;
    glm::vec2 textureCoordinates;
    
    SunBasicVertex(glm::vec2 _position, glm::vec2 _textureCoordinates) {
        position = _position;
        textureCoordinates = _textureCoordinates;
    }
    
    SunBasicVertex() {
        
    }
};

class SunGUIItemMesh {
public:
    SunGUIItemMesh() { }
    
    void setUpGL();
    
    void loadTexture(string texturePath);
    
    void render(glm::vec2 _position, glm::vec2 _size, glm::vec3 _color, GLboolean _textured, glm::vec3 _highlightColor, GLboolean _highlighted, string _text, string _font, SunTextRenderer *_renderer);
    
    inline vector<SunBasicVertex> & getVertices() { return vertices; }
    inline vector<GLuint> & getIndices() { return indices; }
    inline vector<GLuint> & getTextures() { return textures; }
    inline SunShader & getShader() { return shader; }
    inline GLuint getVBO() { return VBO; }
    inline GLuint getEBO() { return EBO; }
    inline GLuint getVAO() { return VAO; }
    inline GLuint getTexture() { return texture; }
private:
    // Vertices and Indices
    vector<SunBasicVertex> vertices = {
        SunBasicVertex(glm::vec2(1.0, 1.0), glm::vec2(1.0, 0.0)),
        SunBasicVertex(glm::vec2(0.0, 1.0), glm::vec2(0.0, 0.0)),
        SunBasicVertex(glm::vec2(0.0, 0.0), glm::vec2(0.0, 1.0)),
        SunBasicVertex(glm::vec2(1.0, 0.0), glm::vec2(1.0, 1.0))
    };
    vector<GLuint> indices = {
        0, 1, 2,
        0, 3, 2
    };
    vector<GLuint> textures;

    // Shader
    SunShader shader = SunShader("../../Engine/Shaders/2DQuad.vert", "../../Engine/Shaders/2DQuad.frag");

    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    GLuint texture;
};

#endif
