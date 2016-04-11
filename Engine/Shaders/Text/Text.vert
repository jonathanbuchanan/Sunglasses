// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 textureCoordinates;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0f, 1.0f);
    gl_Position.z = -1.0;
    textureCoordinates = vertex.zw;
}
