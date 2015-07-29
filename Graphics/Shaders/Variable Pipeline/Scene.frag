
#ifdef OUTPUT_COLOR_0
layout (location = 0) out vec4 color;
#endif
#ifdef OUTPUT_POSITION_0
layout (location = 0) out vec4 position;
#endif

#ifdef OUTPUT_NORMAL_1
layout (location = 1) out vec3 normal;
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

struct Camera {
    float FOV;
    float nearPlane;
    float farPlane;
};

uniform Camera camera;

#ifdef OUTPUT_DEPTH_SS
float linearDepth(float _depth, Camera _camera) {
    float z = _depth * 2.0 - 1.0;
    return (2.0 * _camera.nearPlane * _camera.farPlane) / (_camera.farPlane + _camera.nearPlane - z * (_camera.farPlane - _camera.nearPlane));
}
#endif

void main() {
    #ifdef OUTPUT_COLOR
    #ifdef RENDER_TEXTURED
        color = vec4(texture(material.diffuse, _input.textureCoordinates));
    #endif
    #ifdef RENDER_SOLID
        color = vec4(material.diffuse, 1.0);
    #endif
    #endif
    
    #ifdef OUTPUT_POSITION
        position.xyz = _input.position;
    #endif

    #ifdef OUTPUT_DEPTH_SS
        position.w = linearDepth(gl_FragCoord.z, camera);
    #endif
    
    #ifdef OUTPUT_NORMAL
        normal = _input.normal;
    #endif
}