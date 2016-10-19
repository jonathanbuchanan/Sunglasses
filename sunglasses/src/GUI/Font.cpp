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
}

} // namespace
} // namespace
