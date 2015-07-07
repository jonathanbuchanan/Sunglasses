//
//  SunTexturedQuad.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 7/7/15.
//
//

#ifndef Sunglasses_SunTexturedQuad_h
#define Sunglasses_SunTexturedQuad_h

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

#include "SunPrimitives.h"

class SunTexturedQuad {
public:
    // Vertices, indices, and textures
    vector<SunVertex> vertices = {
        SunVertex(glm::vec3(1.0, 1.0, 0.0), glm::vec2(1.0, 1.0)),
        SunVertex(glm::vec3(1.0, -1.0, 0.0), glm::vec2(1.0, 0.0)),
        SunVertex(glm::vec3(-1.0, -1.0, 0.0), glm::vec2(0.0, 0.0)),
        SunVertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec2(0.0, 1.0))
    };
    vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0
    };
    
    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
    
    // Shader
    SunShader shader;
    
    SunTexturedQuad() {
        
    }
    
    void setUpGL() {
        shader = SunShader("2DFullscreenQuadVertex.vert", "2DFullscreenQuadFragment.frag");
        
        // Generate the VAO
        glGenVertexArrays(1, &VAO);
        
        // Generate the VBO and EBO
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        // Initialize and write the data for the VBO
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SunVertex), &vertices[0], GL_STATIC_DRAW);
        
        // Bind the EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        
        // Initialize and write the data for the EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        
        // Initialize and set the vertex attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)0);
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)offsetof(SunVertex, textureCoordinates));
        
        // Unbind the VBO and EBO
        glBindVertexArray(0);
    }
    
    void render(GLuint _textureID) {
        shader.use();
        
        glBindTexture(GL_TEXTURE_2D, _textureID);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(shader.program, "backgroundTexture"), 0);
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Draw the triangles
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        // Unbind the VAO
        glBindVertexArray(0);
    }
    
private:
    
};

#endif
