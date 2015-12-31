#version 330 core
layout (location = 0) in vec3 position;
layout (location = 4) in ivec4 boneIDs;
layout (location = 5) in vec4 boneWeights;

uniform mat4 lightMatrix;
uniform mat4 model;

uniform mat4 boneMatrices[64];

void main() {
    mat4 finalBoneTransform = boneMatrices[0] * boneWeights[0];
    finalBoneTransform += boneMatrices[1] * boneWeights[1];
    
    gl_Position = lightMatrix * model * finalBoneTransform * vec4(position, 1.0f);
}