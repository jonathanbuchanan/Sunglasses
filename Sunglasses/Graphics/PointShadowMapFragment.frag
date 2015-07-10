#version 330 core
in vec4 outFragmentPosition;

uniform vec3 lightPosition;
uniform float farPlane;

void main() {
    float lightDistance = length(outFragmentPosition.xyz - lightPosition);
    
    lightDistance = lightDistance / farPlane;
    
    gl_FragDepth = lightDistance;
}