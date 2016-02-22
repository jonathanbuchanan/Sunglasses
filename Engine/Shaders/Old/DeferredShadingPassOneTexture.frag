// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) out vec4 position;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 color;

struct Material {
    sampler2D diffuse;
    float shininess;
};

in vec3 outFragmentPosition;
in vec2 outTextureCoordinates;
in vec4 outLightSpaceFragmentPosition;
in vec3 outNormal;

uniform Material material;

void main() {
    position = vec4(outFragmentPosition, 1.0f);
    normal = vec4(normalize(outNormal), 1.0f);
    color = vec4(vec3(texture(material.diffuse, outTextureCoordinates)), 1.0f);
}