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
#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/gtc/quaternion.hpp"
#include "../Libraries/glm/gtx/quaternion.hpp"
#include "../Libraries/glm/gtx/string_cast.hpp"

#include "./SunPrimitives.h"

typedef map<string, GLuint>::iterator SunTextureMapIterator;

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
    
    SunTexturedQuad() {
        
    }
    
    void setUpGL() {
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
    
    void render(map<string, GLuint> _textures, SunShader _shader, vector<SunShaderUniform> _uniforms) {
        _shader.use();
        
        for (int i = 0; i < _uniforms.size(); i++) {
            if (_uniforms[i].type == "float")
                glUniform1f(glGetUniformLocation(_shader.program, _uniforms[i].name.c_str()), *(GLfloat *)_uniforms[i].value);
            else if (_uniforms[i].type == "boolean")
                glUniform1i(glGetUniformLocation(_shader.program, _uniforms[i].name.c_str()), *(GLboolean *)_uniforms[i].value);
        }
        
        int iteratorIndex = 0;
        for (SunTextureMapIterator iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
            glActiveTexture(GL_TEXTURE0 + iteratorIndex);
            glBindTexture(GL_TEXTURE_2D, iterator->second);
            glUniform1i(glGetUniformLocation(_shader.program, iterator->first.c_str()), iteratorIndex);

            iteratorIndex++;
        }
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Draw the triangles
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        // Unbind the VAO
        glBindVertexArray(0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void render(map<string, GLuint> _textures, SunShader _shader) {
        _shader.use();
        
        int iteratorIndex = 0;
            for (SunTextureMapIterator iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
                glActiveTexture(GL_TEXTURE0 + iteratorIndex);
                glBindTexture(GL_TEXTURE_2D, iterator->second);
                glUniform1i(glGetUniformLocation(_shader.program, iterator->first.c_str()), iteratorIndex);
                
                iteratorIndex++;
            }
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Draw the triangles
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        // Unbind the VAO
        glBindVertexArray(0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void renderWithUsedShader(map<string, GLuint> _textures, SunShader _shader) {
        int iteratorIndex = 0;
        for (SunTextureMapIterator iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
            glActiveTexture(GL_TEXTURE0 + iteratorIndex);
            glBindTexture(GL_TEXTURE_2D, iterator->second);
            glUniform1i(glGetUniformLocation(_shader.program, iterator->first.c_str()), iteratorIndex);

            iteratorIndex++;
        }
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Draw the triangles
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        // Unbind the VAO
        glBindVertexArray(0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
private:
    
};

#endif
