// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNFONTRESOURCE_H
#define SUNFONTRESOURCE_H

#include "../Extern/SunResource.h"

#include <string>
#include <map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

/// The structure used to represent a font character
struct SunFontCharacter {
    GLuint texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

/// A SunResource subclasss for loading fonts
/**
 * This class is a subclass of SunResource which allows for loading fonts. Because
 * of the way the resource loading system works, the font is loading in init() instead
 * of the constructor.
 */
class SunFontResource : public SunResource {
public:
    /// This constructor initializes the font with a path to the font.
    SunFontResource(std::string _path);

    /// Initializes the font
    /**
     * This member function initializes the font by loading the font file.
     */
    virtual void init();

    /// Gets the character map
    std::map<GLchar, SunFontCharacter> & getCharacters() { return characters; }
private:
    /// The path to the font file
    std::string path;

    /// The map of characters
    std::map<GLchar, SunFontCharacter> characters;
};

#endif
