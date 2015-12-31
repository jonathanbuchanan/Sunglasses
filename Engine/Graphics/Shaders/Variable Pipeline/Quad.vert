
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinates;

out vertex_fragment {
    vec2 textureCoordinates;
} _output;

void main() {
    gl_Position = vec4(position, 0.0f, 1.0f);
    _output.textureCoordinates = textureCoordinates;
}