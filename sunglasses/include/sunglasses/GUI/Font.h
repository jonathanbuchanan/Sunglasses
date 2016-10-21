#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

#include <sunglasses/Core/Library.h>

#include <glm/glm.hpp>

#include <sunglasses/Graphics/Texture.h>

namespace sunglasses {
namespace GUI {

/// A resource class that loads a font
class Font {
public:
    /// The 'parameter' object for the font resource
    struct Parameter {
        /// Constructs the parameter object with a file path
        Parameter(std::string _file);

        /// The file path of the font
        std::string file;
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
private:
    /// The font face object
    FT_Face face;
};

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
private:
    /// The size of the glyph
    glm::ivec2 size;

    /// The texture containing the glyph image
    Texture texture;
};

} // namespace
} // namespace

#endif
