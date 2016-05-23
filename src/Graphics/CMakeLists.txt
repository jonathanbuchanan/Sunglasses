add_sources(
    SunCamera.cpp
    SunMesh.cpp
    SunPrimitives.cpp
    SunRenderer.cpp
    SunRenderNode.cpp
    SunShader.cpp
    SunTexturedQuad.cpp
    SunUniformPasser.cpp
    SunWindowManager.cpp
)

add_subdirectory(Animation)
add_subdirectory(Loaders)
add_subdirectory(RenderNodes)

add_sources_to_parent()
