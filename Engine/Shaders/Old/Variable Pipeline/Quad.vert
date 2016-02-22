// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;

out vertex_fragment {
    vec2 textureCoordinates;
} _output;

void main() {
    gl_Position = vec4(position, 1.0f);
    _output.textureCoordinates = textureCoordinates;
}
