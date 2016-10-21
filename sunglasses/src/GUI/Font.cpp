#include <sunglasses/GUI/Font.h>

namespace sunglasses {
namespace GUI {

Font::Parameter::Parameter(std::string _file) : file(_file) {

}

Font::LibraryParameter::LibraryParameter() {
    FT_Error error = FT_Init_FreeType(&library);

    // Throw an exception if the library failed
    //if (error)
}

Font::Font(Parameter parameter, const LibraryParameter &library) {
    FT_Error error = FT_New_Face(library.library, parameter.file.c_str(), 0, &face);

    // Throw an exception if loading failed
    //if (error)

    // Set the pixel size
    error = FT_Set_Pixel_Sizes(face, 0, 16);

    // Throw an exception if sizing failed
    //if (error)

}

Glyph::Parameter::Parameter(unsigned long _character) : character(_character) {

}

Glyph::LibraryParameter::LibraryParameter(const FT_Face &_face) : face(_face) {

}

Glyph::Glyph(Parameter parameter, const LibraryParameter &library) {
    unsigned int glyphIndex = FT_Get_Char_Index(library.face, parameter.character);

    // Throw an exception if character has no index
    //if (glyphIndex == 0)

    FT_Error error = FT_Load_Glyph(library.face, glyphIndex, FT_LOAD_RENDER);
    // Throw an exception if loading failed
    //if (error)

    // Convert the glyph to a bitmap
    error = FT_Render_Glyph(library.face->glyph, FT_RENDER_MODE_NORMAL);

    // Throw an error if rendering failed
    //if (error)

    size = glm::ivec2(library.face->glyph->bitmap.width, library.face->glyph->bitmap.rows);
}

} // namespace
} // namespace
