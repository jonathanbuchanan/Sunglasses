// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinates;

out vec3 outFragmentPosition;
out vec3 outNormal;
out vec2 outTextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    outFragmentPosition = vec3(model * vec4(position, 1.0f));
    outNormal = mat3(transpose(inverse(model))) * normal;
    outTextureCoordinates = textureCoordinates;
}