// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;

void main() {
    color = texture(skybox, TexCoords);
}