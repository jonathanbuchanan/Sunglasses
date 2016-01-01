// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
in vec4 outFragmentPosition;

uniform vec3 lightPosition;
uniform float farPlane;

void main() {
    float lightDistance = length(outFragmentPosition.xyz - lightPosition);
    
    lightDistance = lightDistance / farPlane;
    
    gl_FragDepth = lightDistance;
}