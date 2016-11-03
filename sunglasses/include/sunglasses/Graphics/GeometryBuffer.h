#ifndef GEOMETRYBUFFER_H
#define GEOMETRYBUFFER_H

#include <sunglasses/Graphics/Vertex.h>

namespace sunglasses {

/// A object that contains a buffer of geometry data
template<template<size_t, size_t, size_t> class... T>
class GeometryBuffer {
public:
    GeometryBuffer() {
        // Generate the VAO
        glGenVertexArrays(1, &VAO);

        // Bind the VAO
        glBindVertexArray(VAO);


        // Create the VBO
        glGenBuffers(1, &VBO);

        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);


        // Enable vertex attributes
        Vertex_T::attribute();


        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Unbind the VAO
        glBindVertexArray(0);
    }
private:
    /// The vertex type
    typedef WIP::Vertex<T...> Vertex_T;

    /// The vertex array object referencing vertex data
    GLuint VAO;

    /// The vertex buffer object containing vertex data
    GLuint VBO;
};

} // namespace

#endif
