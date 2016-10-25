add_sources(
    Camera.cpp
    Mesh.cpp
    Primitives.cpp
    Renderer.cpp
    RenderNode.cpp
    Shader.cpp
    Texture.cpp
    TexturedQuad.cpp
    WindowManager.cpp
    Vertex.cpp
)

add_subdirectory(Loaders)
add_subdirectory(RenderNodes)

add_sources_to_parent()
