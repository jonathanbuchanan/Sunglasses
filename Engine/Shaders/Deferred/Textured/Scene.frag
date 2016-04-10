// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core

layout (location = 0) out vec4 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec4 color;

in vertex_fragment {
    vec3 position;
    vec2 textureCoordinates;
    vec3 normal;
} _input;

struct Material {
    sampler2D diffuse;
    float shininess;
};
uniform Material material;

void main() {
    color = vec4(texture(material.diffuse, _input.textureCoordinates));
    position.xyz = _input.position;
    normal = _input.normal;
}
