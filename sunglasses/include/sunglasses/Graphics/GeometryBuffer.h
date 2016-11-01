#ifndef GEOMETRYBUFFER_H
#define GEOMETRYBUFFER_H

#include <sunglasses/Graphics/Vertex.h>

namespace sunglasses {

/// A object that contains a buffer of geometry data
template<template<int> class... T>
class GeometryBuffer {
public:

private:
    /// The vertex array object referencing vertex data
    GLuint VAO;
};

} // namespace

#endif
