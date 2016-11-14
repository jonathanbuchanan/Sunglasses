#ifndef GEOMETRYBUFFER_H
#define GEOMETRYBUFFER_H

#include <sunglasses/Graphics/Vertex.h>

#include <initializer_list>
#include <vector>
#include <numeric>

namespace sunglasses {

/// A object that contains a buffer of geometry data
template<template<size_t, typename> class... T>
class GeometryBuffer {
public:
    /// The vertex type
    typedef WIP::Vertex<T...> Vertex_T;

    /// Constructs the buffer from a set of vertices and indices
    GeometryBuffer(std::initializer_list<Vertex_T> _vertices, std::initializer_list<size_t> _indices) :
            vertices(_vertices), indices(_indices) {
        createBuffers();
    }

    /// Constructs the buffer from a set of vertices
    GeometryBuffer(std::initializer_list<Vertex_T> _vertices) :
            vertices(_vertices), indices(vertices.size()) {
        std::iota(indices.begin(), indices.end(), 0);
        createBuffers();
    }

    /// Constructs the buffer from another vector of vertices and indices
    GeometryBuffer(const std::vector<Vertex_T> &_vertices, const std::vector<size_t> &_indices) :
            vertices(_vertices), indices(_indices) {
        createBuffers();
    }

    /// Constructs the buffer from another vector of vertices
    GeometryBuffer(const std::vector<Vertex_T> &_vertices) :
            vertices(_vertices), indices(vertices.size()) {
        std::iota(indices.begin(), indices.end(), 0);
        createBuffers();
    }
private:
    /// Creates the OpenGL buffers
    void createBuffers() {
        // Generate the VAO
        glGenVertexArrays(1, &VAO);

        // Bind the VAO
        glBindVertexArray(VAO);


        // Create the VBO
        glGenBuffers(1, &VBO);

        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Fill the VBO with data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex_T), vertices.data(), GL_STATIC_DRAW);


        // Generate the EBO
        glGenBuffers(1, &EBO);

        // Bind the EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Fill the EBO with data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(size_t), indices.data(), GL_STATIC_DRAW);


        // Enable vertex attributes
        Vertex_T::attribute();

        // Set the vertex attribute pointer
        Vertex_T::attributePointers();


        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Unbind the EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Unbind the VAO
        glBindVertexArray(0);
    }

    /// The vector containing vertex data
    std::vector<Vertex_T> vertices;

    /// The vector containing index data
    std::vector<size_t> indices;

    /// The vertex array object referencing vertex data
    GLuint VAO;

    /// The vertex buffer object containing vertex data
    GLuint VBO;

    /// The element buffer object containing index data
    GLuint EBO;
};

} // namespace

#endif
