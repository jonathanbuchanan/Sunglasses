// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
in vec2 outTextureCoordinates;
out vec4 color;

uniform sampler2D backgroundTexture;

uniform bool horizontal;

uniform float blurWeights[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
    vec2 texelOffset = 1.0 / textureSize(backgroundTexture, 0);
    vec3 result = texture(backgroundTexture, outTextureCoordinates).rgb * blurWeights[0];
    if (horizontal) {
        for (int i = 1; i < 5; ++i) {
            result += texture(backgroundTexture, outTextureCoordinates + vec2(texelOffset.x * i, 0.0)).rgb * blurWeights[i];
            result += texture(backgroundTexture, outTextureCoordinates - vec2(texelOffset.x * i, 0.0)).rgb * blurWeights[i];
        }
    } else {
        for (int i = 1; i < 5; ++i) {
            result += texture(backgroundTexture, outTextureCoordinates + vec2(0.0, texelOffset.y * i)).rgb * blurWeights[i];
            result += texture(backgroundTexture, outTextureCoordinates - vec2(0.0, texelOffset.y * i)).rgb * blurWeights[i];
        }
    }
    color = vec4(result, 1.0);
}