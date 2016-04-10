// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
layout (location = 0) out vec4 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec4 color;

in vertex_fragment {
    vec3 position;
    vec2 textureCoordinates;
    vec3 normal;
} _input;

struct Material {
    vec3 diffuse;
    float shininess;
};
uniform Material material;

void main() {
    color = vec4(material.diffuse, 1.0);
    position.xyz = _input.position;
    normal = _input.normal;
}
