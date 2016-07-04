// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNUNIFORMPASSER_H
#define SUNUNIFORMPASSER_H

#include "../Core/SunBase.h"
#include "SunShader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>

struct SunUniformBuffer {
    GLuint buffer;
    GLuint bindingPoint;
};

class SunUniformPasser : public SunBase {
public:
    virtual void init();

    void createBuffer(std::string name, GLuint size);
    void bindBufferToShader(std::string block, SunShader shader);
    void bufferSubData(std::string block, GLuint offset, GLuint length, const GLvoid *data);
protected:
    std::map<std::string, SunUniformBuffer> uniformBuffers;
    inline void addBuffer(std::string s, SunUniformBuffer b) { uniformBuffers[s] = b; }

    static GLuint bindingPoint;

    inline GLuint getNewBindingPoint() { GLuint x = bindingPoint; bindingPoint++; return x; }
};

#endif
