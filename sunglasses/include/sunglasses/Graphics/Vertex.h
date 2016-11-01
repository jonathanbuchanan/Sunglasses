#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <utility>

namespace sunglasses {

namespace WIP {

/// A base class for vertex attributes
template<size_t N>
struct VertexAttribute {
    /// Enables the respective vertex attribute array
    static void vertexAttribute() {
        glEnableVertexAttribArray(N);
    }
};

/// An object containing a position in one-dimensional space
template<size_t N>
struct Position1 : public VertexAttribute<N> {
    /// The position
    float position;
};

/// An object containing a position in two-demensional space
template<size_t N>
struct Position2 : public VertexAttribute<N> {
    /// The position
    glm::vec2 position;
};

/// An object containing a position in three-dimensional space
template<size_t N>
struct Position3 : public VertexAttribute<N> {
    /// The position
    glm::vec3 position;
};

/// An object containing a position in four-dimensional space
template<size_t N>
struct Position4 : public VertexAttribute<N> {
    /// The position
    glm::vec4 position;
};


/// An object containing texture-coordinates
template<size_t N>
struct TextureCoordinates : public VertexAttribute<N> {
    /// The texture coordinates
    glm::vec2 textureCoordinates;
};


/// An object containing a normal vector
template<size_t N>
struct Normal : public VertexAttribute<N> {
    /// The normal vector
    glm::vec3 normal;
};


/// An object containing a tangent vector
template<size_t N>
struct Tangent : public VertexAttribute<N> {
    /// The tangent vector
    glm::vec3 tangent;
};

/// A class for the vertex list
template<class T, template<size_t> class... Ts>
struct VertexComponents {

};

template<size_t... I, template<size_t> class... Ts>
struct VertexComponents<std::index_sequence<I...>, Ts...> : Ts<I>... {
    /// Enables its vertex attributes
    static void attribute() {
        (void)std::initializer_list<int>{ (Ts<I>::vertexAttribute(), 0)... };
    }
};

/// An object containing vertex data
template<template<size_t> class... T>
using Vertex = VertexComponents<std::make_index_sequence<sizeof...(T)>, T...>;

}
} // namespace

#endif
