// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/SunUniformPasser.h>

GLuint SunUniformPasser::bindingPoint = 0;

void SunUniformPasser::createBuffer(std::string name, GLuint size) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);

    GLuint bindingPoint = getNewBindingPoint();
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    SunUniformBuffer ubo;
    ubo.buffer = buffer;
    ubo.bindingPoint = bindingPoint;

    addBuffer(name, ubo);
}

void SunUniformPasser::bindBufferToShader(std::string block, SunShader shader) {
    GLuint blockIndex = glGetUniformBlockIndex(shader.getProgram(), block.c_str());
    glUniformBlockBinding(shader.getProgram(), blockIndex, uniformBuffers[block].bindingPoint);
}

void SunUniformPasser::bufferSubData(std::string block, GLuint offset, GLuint length, const GLvoid *data) {
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffers[block].buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, length, data);
}
