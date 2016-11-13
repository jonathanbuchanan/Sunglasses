#ifndef GEOMETRYBUFFER_H
#define GEOMETRYBUFFER_H

#include <sunglasses/Graphics/Vertex.h>

namespace sunglasses {

/// A object that contains a buffer of geometry data
template<template<size_t, typename> class... T>
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


        // Generate the EBO
        glGenBuffers(1, &EBO);

        // Bind the EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


        // Enable vertex attributes
        Vertex_T::attribute();

        // Set the vertex attribute pointer
        Vertex_T::attributePointers();


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

    /// The element buffer object containing index data
    GLuint EBO;
};

} // namespace

#endif
