// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
out vec4 color;
in vec2 outTextureCoordinates;

uniform sampler2D depthMap;

void main() {
    float depthValue = texture(depthMap, outTextureCoordinates).r;
    color = vec4(vec3(depthValue), 1.0);
}