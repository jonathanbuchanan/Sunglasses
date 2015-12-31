// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 model;

void main() {
    gl_Position = model * vec4(position, 1.0);
}