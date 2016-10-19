#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

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
    struct Library {
        /// Constructs the library object by creating a Freetype library
        Library();

        /// The Freetype library
        FT_Library library;
    };

    /// Constructs the font from the 'parameter' object and 'library' object
    Font(Parameter p, const Library &l);
private:
    /// The font face object
    FT_Face face;
};

} // namespace
} // namespace

#endif
