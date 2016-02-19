// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec2 textureCoordinates;
layout (location = 4) in ivec4 boneIDs;
layout (location = 5) in vec4 boneWeights;

out vec3 outFragmentPosition;
out vec4 outLightSpaceFragmentPosition;
out vec3 outTangentLightPosition;
out vec3 outTangentViewPosition;
out vec3 outTangentFragmentPosition;
out vec2 outTextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightMatrix;
uniform mat4 boneMatrices[64];
uniform bool animate;

struct PointLight {
    // Diffuse and specular
    vec3 diffuseColor;
    vec3 specularColor;
    
    // Position
    vec3 position;
    
    // Attenuation
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLight;
uniform vec3 viewPosition;

void main() {
    mat4 finalBoneTransform = boneMatrices[0] * boneWeights[0];
    finalBoneTransform += boneMatrices[1] * boneWeights[1];
    
    vec4 bonePosition = finalBoneTransform * vec4(position, 1.0f);
    if (animate == false)
        bonePosition = vec4(position, 1.0f);
    
    gl_Position = projection * view * model * bonePosition;
    
    outFragmentPosition = vec3(model * vec4(position, 1.0f));
    
    outLightSpaceFragmentPosition = lightMatrix * vec4(outFragmentPosition, 1.0f);
    
    outTextureCoordinates = textureCoordinates;
    
    vec3 bitangent = cross(normal, tangent);
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    
    vec3 _tangent = normalize(normalMatrix * normal);
    vec3 _bitangent = normalize(normalMatrix * bitangent);
    vec3 _normal = normalize(normalMatrix * normal);
    
    mat3 TBN = transpose(mat3(_tangent, _bitangent, _normal));
    
    outTangentLightPosition = TBN * pointLight.position;
    outTangentViewPosition = TBN * viewPosition;
    outTangentFragmentPosition = TBN * outFragmentPosition;
}