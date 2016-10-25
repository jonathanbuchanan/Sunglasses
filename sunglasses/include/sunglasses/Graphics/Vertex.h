#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace sunglasses {

namespace WIP {

/// An object containing a position in one-dimensional space
struct Position1 {
    /// The position
    float position;
};

/// An object containing a position in two-demensional space
struct Position2 {
    /// The position
    glm::vec2 position;
};

/// An object containing a position in three-dimensional space
struct Position3 {
    /// The position
    glm::vec3 position;
};

/// An object containing a position in four-dimensional space
struct Position4 {
    /// The position
    glm::vec4 position;
};


/// An object containing texture-coordinates
struct TextureCoordinates {
    /// The texture coordinates
    glm::vec2 textureCoordinates;
};


/// An object containing a normal vector
struct Normal {
    /// The normal vector
    glm::vec3 normal;
};


/// An object containing a tangent vector
struct Tangent {
    /// The tangent vector
    glm::vec3 tanget;
};


/// An object containing vertex data
template<typename... T>
struct Vertex : T... {

};

}

} // namespace

#endif
