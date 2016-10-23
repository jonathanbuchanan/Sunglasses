#include <sunglasses/GUI/Font.h>

namespace sunglasses {
namespace GUI {

Glyph::Parameter::Parameter(unsigned long _character) : character(_character) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

Glyph::LibraryParameter::LibraryParameter(const FT_Face &_face) : face(_face) {

}

Glyph::Glyph(Parameter parameter, const LibraryParameter &library) :
        slot(loadGlyph(parameter.character, library.face)),
        size(slot->bitmap.width, slot->bitmap.rows),
        bearing(slot->bitmap_left, slot->bitmap_top),
        advance(slot->advance.x, slot->advance.y),
        texture(Image(size, slot->bitmap.buffer, Texture::InternalFormat::Red, Texture::Format::Red)) {

}

FT_GlyphSlot Glyph::loadGlyph(unsigned long character, const FT_Face &face) {
    // Get the glyph index
    unsigned int glyphIndex = FT_Get_Char_Index(face, character);

    // Throw an exception if character has no index
    //if (glyphIndex == 0)

    FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
    // Throw an exception if loading failed
    //if (error)

    // Convert the glyph to a bitmap
    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

    // Throw an error if rendering failed
    //if (error)

    return face->glyph;
}

Font::Parameter::Parameter(std::string _file, glm::ivec2 _size) :
        file(_file), size(_size) {

}

Font::Parameter::Parameter(std::string _file, glm::vec2 pointSize, glm::ivec2 resolution) :
        file(_file) {

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
    error = FT_Set_Pixel_Sizes(newFace, 0, 48);

    // Throw an exception if sizing failed
    //if (error)

    return newFace;
}

} // namespace
} // namespace
