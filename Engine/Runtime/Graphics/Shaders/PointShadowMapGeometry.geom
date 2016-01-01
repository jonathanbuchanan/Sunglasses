// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

uniform mat4 lightMatrices[6];

out vec4 outFragmentPosition;

void main() {
    for (int face = 0; face < 6; ++face) {
        gl_Layer = face;
        for(int i = 0; i < 3; ++i) {
            outFragmentPosition = gl_in[i].gl_Position;
            gl_Position = lightMatrices[face] * outFragmentPosition;
            EmitVertex();
        }
        EndPrimitive();
    }
}