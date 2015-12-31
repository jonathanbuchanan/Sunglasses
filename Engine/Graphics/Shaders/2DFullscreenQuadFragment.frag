// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
in vec2 outTextureCoordinates;
out vec4 color;

struct Textures {
    sampler2D backgroundTexture;
    sampler2D bloomTexture;
};

uniform Textures t;

uniform float exposure;
uniform bool doHDR;

void main() {
    vec3 nonclamped = vec3(texture(t.backgroundTexture, outTextureCoordinates));
    vec3 bloom = vec3(texture(t.bloomTexture, outTextureCoordinates));
    
    nonclamped += bloom;
    
    vec3 result = vec3(1.0f) - exp(-nonclamped * exposure);
    
    color = vec4(vec3(texture(t.backgroundTexture, outTextureCoordinates)), 1.0f);
}