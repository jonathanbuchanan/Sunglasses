
#ifdef OUTPUT_COLOR_0
layout (location = 0) out vec4 color;
#endif
#ifdef OUTPUT_POSITION_0
layout (location = 0) out vec4 position;
#endif

#ifdef OUTPUT_NORMAL_1
layout (location = 1) out vec4 normal;
#endif

#ifdef OUTPUT_COLOR_2
layout (location = 2) out vec4 color;
#endif

in vertex_fragment {
    vec3 position;
    vec2 textureCoordinates;
    vec3 normal;
} _input;

#ifdef RENDER_TEXTURED
struct Material {
    sampler2D diffuse;
    float shininess;
};
uniform Material material;
#endif
#ifdef RENDER_SOLID
struct Material {
    vec3 diffuse;
    float shininess;
};
uniform Material material;
#endif

void main() {
    #ifdef OUTPUT_COLOR
    #ifdef RENDER_TEXTURED
        color = vec4(texture(material.diffuse, _input.textureCoordinates));
    #endif
    #ifdef RENDER_SOLID
        color = material.diffuse;
    #endif
    #endif
    
    #ifdef OUTPUT_POSITION
        position = _input.position;
    #endif
    
    #ifdef OUTPUT_NORMAL
        normal = _input.normal;
    #endif
}