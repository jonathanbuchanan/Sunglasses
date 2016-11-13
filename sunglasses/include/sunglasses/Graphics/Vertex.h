#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <utility>

namespace sunglasses {

namespace WIP {

namespace utility {

template<typename T, typename M>
inline size_t constexpr offset_of(M T::*member) {
    constexpr T object {};
    return size_t(&(object.*member)) - size_t(&object);
}


template<typename T>
using Attribute_T = typename T::Attribute_T;

}

/// A base class for vertex attributes
template<size_t N>
struct VertexAttribute {
    /// Enables the respective vertex attribute array
    static void vertexAttribute() {
        glEnableVertexAttribArray(N);
    }
};

/// An object containing a position in one-dimensional space
template<size_t N, typename T>
struct Position1 : public VertexAttribute<N> {
    /// The position
    float position;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::position);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 1, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    Position1(float _position) : position{_position} {}

    /// The type of the attribute
    using Attribute_T = float;
};

/// An object containing a position in two-demensional space
template<size_t N, typename T>
struct Position2 : public VertexAttribute<N> {
    /// The position
    glm::vec2 position;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::position);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    Position2(glm::vec2 _position) : position{_position} {}

    /// The type of the attribute
    using Attribute_T = glm::vec2;
};

/// An object containing a position in three-dimensional space
template<size_t N, typename T>
struct Position3 : public VertexAttribute<N> {
    /// The position
    glm::vec3 position;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::position);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    Position3(glm::vec3 _position) : position{_position} {}

    /// The type of the attribute
    using Attribute_T = glm::vec3;
};

/// An object containing a position in four-dimensional space
template<size_t N, typename T>
struct Position4 : public VertexAttribute<N> {
    /// The position
    glm::vec4 position;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::position);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    Position4(glm::vec4 _position) : position{_position} {}

    /// The type of the attribute
    using Attribute_T = glm::vec4;
};


/// An object containing texture-coordinates
template<size_t N, typename T>
struct TextureCoordinates : public VertexAttribute<N> {
    /// The texture coordinates
    glm::vec2 textureCoordinates;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::textureCoordinate);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    TextureCoordinates(glm::vec2 _textureCoordinates) : textureCoordinates{_textureCoordinates} {}

    /// The type of the attribute
    using Attribute_T = glm::vec2;
};


/// An object containing a normal vector
template<size_t N, typename T>
struct Normal : public VertexAttribute<N> {
    /// The normal vector
    glm::vec3 normal;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::normal);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    Normal(glm::vec3 _normal) : normal{_normal} {}

    /// The type of the attribute
    using Attribute_T = glm::vec3;
};


/// An object containing a tangent vector
template<size_t N, typename T>
struct Tangent : public VertexAttribute<N> {
    /// The tangent vector
    glm::vec3 tangent;

    /// The stride of the attribute
    static const int stride = sizeof(T);

    /// The offset of the attribute
    static const int offset = utility::offset_of(&T::tangent);

    /// Registers the vertex attribute pointer
    static void vertexAttributePointer() {
        glVertexAttribPointer(N, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
    }

    /// Constructs the attribute
    Tangent(glm::vec3 _tangent) : tangent{_tangent} {}

    /// The type of the attribute
    using Attribute_T = glm::vec3;
};

/// A class for the vertex list
template<class I, template<size_t, typename> class... Ts>
struct VertexComponents {

};

template<size_t... I, template<size_t, typename> class... Ts>
struct VertexComponents<std::index_sequence<I...>, Ts...> : Ts<I, VertexComponents<std::index_sequence<I...>, Ts...>>... {
    /// Constructs the vertex from its attributes
    VertexComponents(utility::Attribute_T<Ts<I, VertexComponents<std::index_sequence<I...>, Ts...>>>... attributes) :
            Ts<I, VertexComponents<std::index_sequence<I...>, Ts...>>{attributes}... {}

    /// Enables its vertex attributes
    static void attribute() {
        (void)std::initializer_list<int>{ (Ts<I, VertexComponents<std::index_sequence<I...>, Ts...>>::vertexAttribute(), 0)... };
    }

    /// Registers all the vertex attribute pointers
    static void attributePointers() {
        (void)std::initializer_list<int>{ (Ts<I, VertexComponents<std::index_sequence<I...>, Ts...>>::vertexAttributePointer(), 0)... };
    }
};

/// An object containing vertex data
/**
 * The template parameters passed to this class are the different
 * attributes of the vertex. They are automatically assigned an
 * index at compile-time.
 *
 * The constructor for a vertex accepts constructor arguments for its attributes.
 * This means that it can be brace-initialized with its attribute values.
 *
 * @warning The attributes must be passed in the same order as the indices
 * in the shader code
 */
template<template<size_t, typename> class... T>
using Vertex = VertexComponents<std::make_index_sequence<sizeof...(T)>, T...>;

}
} // namespace

#endif
