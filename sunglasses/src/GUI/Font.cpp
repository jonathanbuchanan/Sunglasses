#include <sunglasses/GUI/Font.h>

namespace sunglasses {
namespace GUI {

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

    // Set the size of the glyph
    size = glm::ivec2(library.face->glyph->bitmap.width, library.face->glyph->bitmap.rows);

    // Load the bitmap
    glGenTextures(1, &texture);

    glBindTexture(texture, GL_TEXTURE_2D);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, library.face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(texture, 0);
}

Font::Parameter::Parameter(std::string _file) : file(_file) {

}

Font::LibraryParameter::LibraryParameter() {
    FT_Error error = FT_Init_FreeType(&library);

    // Throw an exception if the library failed
    //if (error)
}

Font::Font(Parameter parameter, const LibraryParameter &library) :
        face(loadFace(parameter.file, library.library)), glyphs(Glyph::LibraryParameter(face)) {

}

FT_Face Font::loadFace(std::string file, FT_Library library) {
    FT_Face newFace;

    FT_Error error = FT_New_Face(library, file.c_str(), 0, &newFace);

    // Throw an exception if loading failed
    //if (error)

    // Set the pixel size
    error = FT_Set_Pixel_Sizes(newFace, 0, 16);

    // Throw an exception if sizing failed
    //if (error)

    return newFace;
}

} // namespace
} // namespace
