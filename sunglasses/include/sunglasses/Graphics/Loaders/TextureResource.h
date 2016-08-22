// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include <sunglasses/Extern/Resource.h>

#include <string>

#include <GL/glew.h>

namespace sunglasses {

class TextureResource : public Resource {
public:
    /// Constructs the texture resource with a path to the texture.
    /**
     * This constructor initializes the file member with the parameter.
     * @param _file The path to the texture
     */
    TextureResource(std::string _file);

    /// Loads the texture from the file.
    void init();

    /// Gets the texture
    GLuint getTexture() { return texture; }
private:
    /// The path to the texture
    std::string file;

    /// The OpenGL texture object
    GLuint texture;
};

} // namespace

#endif
