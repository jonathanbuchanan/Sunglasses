// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinates;

uniform mat4 model;
out vec2 outTextureCoordinates;

void main() {
    gl_Position = model * vec4(position, -0.5f, 1.0f);
    outTextureCoordinates = textureCoordinates;
}