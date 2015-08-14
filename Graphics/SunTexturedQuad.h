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
#include "./Shaders/SunShader.h"

typedef map<string, GLuint>::iterator SunTextureMapIterator;

class SunTexturedQuad {
public:
    SunTexturedQuad() { }
    
    void setUpGL();
    void render(map<string, GLuint> _textures, SunShader _shader);
    void renderWithUsedShader(map<string, GLuint> _textures, SunShader _shader);
    
    inline vector<SunVertex> & getVertices() { return vertices; }
    inline vector<GLuint> & getIndices() { return indices; }
    
    inline GLuint & getVBO() { return VBO; }
    inline GLuint & getEBO() { return EBO; }
    inline GLuint & getVAO() { return VAO; }
private:
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
};

#endif
