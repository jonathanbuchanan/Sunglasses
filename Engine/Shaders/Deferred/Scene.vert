// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec2 textureCoordinates;

out vertex_fragment {
    vec3 position;
    vec2 textureCoordinates;
    vec3 normal;
} _output;

uniform mat4 model;
uniform mat3 normalMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightMatrix;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);

    _output.position = vec4(model * vec4(position, 1.0f)).xyz;
    _output.textureCoordinates = textureCoordinates;
    _output.normal = normalMatrix * normal;
}
