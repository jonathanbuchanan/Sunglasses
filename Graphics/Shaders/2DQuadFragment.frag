#version 330 core
out vec4 color;
in vec2 outTextureCoordinates;

uniform vec3 _color;

uniform bool _textured;
uniform sampler2D _texture;

uniform vec3 _highlightColor;
uniform bool _highlighted;

void main() {
    vec3 textureColor = vec3(texture(_texture, outTextureCoordinates));
    vec3 result = _color;
    
    if (_textured == true) {
        result = vec3(texture(_texture, outTextureCoordinates));
    }
    
    if (_highlighted == true) {
        result = _highlightColor;
    }
    
    color = vec4(result, 1.0f);
}