#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

#include <sunglasses/Core/Library.h>
#include <sunglasses/Graphics/Texture.h>

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace sunglasses {
namespace GUI {

/// A resource class that represents a single glyph in a font
class Glyph {
public:
    /// The 'parameter' object for the glyph resource
    struct Parameter {
        /// Constructs the parameter object with a font face, and a character
        Parameter(unsigned long _character);

        /// The character to load as a glyph
        unsigned long character;
    };

    /// The 'library' object for the glyph resource
    struct LibraryParameter {
        /// Constructs the library object with a font face reference
        LibraryParameter(const FT_Face &_face);

        /// A reference to the font face
        const FT_Face &face;
    };

    /// Constructs the glyph
    Glyph(Parameter p, const LibraryParameter &l);

    /// The library type for this resource
    typedef Library<unsigned long, Glyph, Parameter, LibraryParameter> LibraryT;
//private:
    /// Loads a glyph
    static FT_GlyphSlot loadGlyph(unsigned long character, const FT_Face &face);

    /// The temporary glyph slot
    FT_GlyphSlot slot;

    /// The size of the glyph
    glm::ivec2 size;

    /// The bearing of the glyph
    glm::ivec2 bearing;

    /// The advance of the glyph
    glm::ivec2 advance;

    /// The texture containing the glyph image
    Texture texture;
};

/// A resource class that loads a font
class Font {
public:
    /// The 'parameter' object for the font resource
    struct Parameter {
        /// Constructs the parameter object with a file path and size
        Parameter(std::string _file, glm::ivec2 _size);

        /// Constructs the parameter object with a file path and size
        Parameter(std::string _file, glm::vec2 pointSize, glm::ivec2 resolution);

        /// The file path of the font
        std::string file;

        /// The size of the font in pixels
        glm::ivec2 size;
    };

    /// The 'library' object for the font resource
    struct LibraryParameter {
        /// Constructs the library object by creating a Freetype library
        LibraryParameter();

        /// The Freetype library
        FT_Library library;
    };

    /// Constructs the font from the 'parameter' object and 'library' object
    Font(Parameter p, const LibraryParameter &l);

    /// The library type for this resource
    typedef Library<std::string, Font, Parameter, LibraryParameter> LibraryT;

    /// The library of glyphs
    Glyph::LibraryT glyphs;
private:
    /// Loads a font face from a file
    static FT_Face loadFace(std::string file, FT_Library library, glm::ivec2 size);

    /// The font face object
    FT_Face face;
};

} // namespace
} // namespace

#endif
