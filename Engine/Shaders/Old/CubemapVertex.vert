// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    vec4 _position = projection * view * vec4(position, 1.0);
    gl_Position = _position.xyww;
    TexCoords = position;
}