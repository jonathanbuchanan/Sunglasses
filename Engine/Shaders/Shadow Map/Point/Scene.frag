// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) out float depth;

in geometry_fragment {
    vec4 position;
} _input_geo;

uniform vec3 lightPosition;
uniform float farPlane;

void main() {
    float lightDistance = length(_input_geo.position.xyz - lightPosition);
    lightDistance = lightDistance / farPlane;
    gl_FragDepth = lightDistance;
}
