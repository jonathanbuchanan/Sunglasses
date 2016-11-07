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
template<size_t N, size_t Stride, size_t Offset>
struct Position1 : public VertexAttribute<N> {
    /// The position
    float position;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 1, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};

/// An object containing a position in two-demensional space
template<size_t N, size_t Stride, size_t Offset>
struct Position2 : public VertexAttribute<N> {
    /// The position
    glm::vec2 position;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 2, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};

/// An object containing a position in three-dimensional space
template<size_t N, size_t Stride, size_t Offset>
struct Position3 : public VertexAttribute<N> {
    /// The position
    glm::vec3 position;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};

/// An object containing a position in four-dimensional space
template<size_t N, size_t Stride, size_t Offset>
struct Position4 : public VertexAttribute<N> {
    /// The position
    glm::vec4 position;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 4, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};


/// An object containing texture-coordinates
template<size_t N, size_t Stride, size_t Offset>
struct TextureCoordinates : public VertexAttribute<N> {
    /// The texture coordinates
    glm::vec2 textureCoordinates;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 2, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};


/// An object containing a normal vector
template<size_t N, size_t Stride, size_t Offset>
struct Normal : public VertexAttribute<N> {
    /// The normal vector
    glm::vec3 normal;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};


/// An object containing a tangent vector
template<size_t N, size_t Stride, size_t Offset>
struct Tangent : public VertexAttribute<N> {
    /// The tangent vector
    glm::vec3 tangent;

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, Stride, (GLvoid *)Offset);
    }
};

/// A template class used to retrieve the size of a vertex attribute
template<template<size_t, size_t, size_t> class>
struct VertexAttributeSize {

};

template<>
struct VertexAttributeSize<Position1> {
    static const size_t size = sizeof(GLfloat);
};

template<>
struct VertexAttributeSize<Position2> {
    static const size_t size = 2 * sizeof(GLfloat);
};

template<>
struct VertexAttributeSize<Position3> {
    static const size_t size = 3 * sizeof(GLfloat);
};

template<>
struct VertexAttributeSize<Position4> {
    static const size_t size = 4 * sizeof(GLfloat);
};

template<>
struct VertexAttributeSize<TextureCoordinates> {
    static const size_t size = 2 * sizeof(GLfloat);
};

template<>
struct VertexAttributeSize<Normal> {
    static const size_t size = 3 * sizeof(GLfloat);
};

template<>
struct VertexAttributeSize<Tangent> {
    static const size_t size = 3 * sizeof(GLfloat);
};

namespace utility {

template<int... Ns>
struct sum {

};

template<int N>
struct sum<N> {
    static const int value = N;
};

template<int A, int... Ns>
struct sum<A, Ns...> {
    static const int value = A + sum<Ns...>::value;
};

template<>
struct sum<> {
    static const int value = 0;
};

// Gets the Nth int
template<size_t N, int A, int... Ns>
struct nth_int : nth_int<N - 1, Ns...> {

};

template<int A, int... Ns>
struct nth_int<0, A, Ns...> {
    static const int value = A;
};


template<typename I, int... Ns>
struct gen_sum_nth {

};

template<size_t... Is, int... Ns>
struct gen_sum_nth<std::index_sequence<Is...>, Ns...> {
    static const int value = sum<nth_int<Is, Ns...>::value...>::value;
};

template<size_t N, int... Ns>
using sum_nth = gen_sum_nth<std::make_index_sequence<N>, Ns...>;


template<int... Ns>
struct offset_sequence {

};

template<typename I, int... Ns>
struct gen_offset_sequence {

};

template<size_t... Is, int... Ns>
struct gen_offset_sequence<std::index_sequence<Is...>, Ns...> {
    using type = offset_sequence<sum_nth<Is, Ns...>::value...>;
};

template<int... Ns>
using make_offset_sequence = typename gen_offset_sequence<std::make_index_sequence<sizeof...(Ns)>, Ns...>::type;

}

/// A class for the vertex list
template<class I, class O, size_t Stride, template<size_t, size_t, size_t> class... Ts>
struct VertexComponents {

};

template<size_t Stride, size_t... I, int... O, template<size_t, size_t, size_t> class... Ts>
struct VertexComponents<std::index_sequence<I...>, utility::offset_sequence<O...>, Stride, Ts...> : Ts<I, Stride, O>... {
    /// Enables its vertex attributes
    static void attribute() {
        (void)std::initializer_list<int>{ (Ts<I, Stride, O>::vertexAttribute(), 0)... };
    }

    /// Registers all the vertex attribute pointers
    static void attributePointers() {
        (void)std::initializer_list<int>{ (Ts<I, Stride, O>::vertexAttributePointer(), 0)... };
    }
};

/// An object containing vertex data
/**
 * The template parameters passed to this class are the different
 * attributes of the vertex. They are automatically assigned an
 * index at compile-time.
 * @warning The attributes must be passed in the same order as the indices
 * in the shader code
 */
template<template<size_t, size_t, size_t> class... T>
using Vertex = VertexComponents<std::make_index_sequence<sizeof...(T)>, utility::make_offset_sequence<VertexAttributeSize<T>::size...>, utility::sum<VertexAttributeSize<T>::size...>::value, T...>;

}
} // namespace

#endif
