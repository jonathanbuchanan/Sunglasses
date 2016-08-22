// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace sunglasses {

class Image;

class Shader;

enum struct TextureMinification : GLint {
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR,
    NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
    LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
};

enum struct TextureMagnification : GLint {
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR
};

enum struct TextureWrap : GLint {
    ClampToEdge = GL_CLAMP_TO_EDGE,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    Repeat = GL_REPEAT
};

/// A class that contains an OpenGL texture
class Texture {
friend Shader;
public:
    /// An enum that holds all internal format types
    enum struct InternalFormat : GLint {
        // Base Internal Formats
        DepthComponent = GL_DEPTH_COMPONENT,
        DepthStencil = GL_DEPTH_STENCIL,
        Red = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA,

        // Sized Internal Formats
        R8 = GL_R8,
        R8_SNorm = GL_R8_SNORM,
        R16 = GL_R16,
        R16_SNorm = GL_R16_SNORM,
        RG8 = GL_RG8,
        RG8_SNorm = GL_RG8_SNORM,
        RG16 = GL_RG16,
        RG16_SNorm = GL_RG16_SNORM,
        R3_G3_B2 = GL_R3_G3_B2,
        RGB4 = GL_RGB4,
        RGB5 = GL_RGB5,
        RGB8 = GL_RGB8,
        RGB8_SNorm = GL_RGB8_SNORM,
        RGB10 = GL_RGB10,
        RGB12 = GL_RGB12,
        RGB16_SNorm = GL_RGB16_SNORM,
        RGBA2 = GL_RGBA2,
        RGBA4 = GL_RGBA4,
        RGB5_A1 = GL_RGB5_A1,
        RGBA8 = GL_RGBA8,
        RGBA8_SNorm = GL_RGBA8_SNORM,
        RGB10_A2 = GL_RGB10_A2,
        RGB10_A2UI = GL_RGB10_A2UI,
        RGBA12 = GL_RGBA12,
        RGBA16 = GL_RGBA16,
        SRGB8 = GL_SRGB8,
        SRGB8_A8 = GL_SRGB8_ALPHA8,
        R16F = GL_R16F,
        RG16F = GL_RG16F,
        RGB16F = GL_RGB16F,
        RGBA16F = GL_RGBA16F,
        R32F = GL_R32F,
        RG32F = GL_RG32F,
        RGB32F = GL_RGB32F,
        RGBA32F = GL_RGBA32F,
        R11F_G11F_B10F = GL_R11F_G11F_B10F,
        RGB9_E5 = GL_RGB9_E5,
        R8I = GL_R8I,
        R8UI = GL_R8UI,
        R16I = GL_R16I,
        R16UI = GL_R16UI,
        RG32I = GL_RG32I,
        RG32UI = GL_RG32UI,
        RGB8I = GL_RGB8I,
        RGB8UI = GL_RGB8UI,
        RGB16I = GL_RGB16I,
        RGB16UI = GL_RGB16UI,
        RGB32I = GL_RGB32I,
        RGB32UI = GL_RGB32UI,
        RGBA8I = GL_RGBA8I,
        RGBA8UI = GL_RGBA8UI,
        RGBA16I = GL_RGBA16I,
        RGBA16UI = GL_RGBA16UI,
        RGBA32I = GL_RGBA32I,
        RGBA32UI = GL_RGBA32UI,

        // Compressed Internal Format
        CompressedRed = GL_COMPRESSED_RED,
        CompressedRG = GL_COMPRESSED_RG,
        CompressedRGB = GL_COMPRESSED_RGB,
        CompressedRGBA = GL_COMPRESSED_RGBA,
        CompressedSRGB = GL_COMPRESSED_SRGB,
        CompressedSRGBA = GL_COMPRESSED_SRGB_ALPHA,
        CompressedRed_RGTC1 = GL_COMPRESSED_RED_RGTC1,
        CompressedSignedRed_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
        CompressedRG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
        CompressedSignedRG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
        CompressedRGBA_BPTC_UNorm = GL_COMPRESSED_RGBA_BPTC_UNORM,
        CompressedSRGBA_BPTC_UNorm = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
        CompressedRGB_BPTC_SignedFloat = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
        CompressedRGB_BPTC_UnsignedFloat = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
    };

    /// An enum holding texture input format types
    enum struct Format : GLenum {
        Red = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        BGR = GL_BGR,
        RGBA = GL_RGBA,
        BGRA = GL_BGRA,
        DepthComponent = GL_DEPTH_COMPONENT,
        DepthStencil = GL_DEPTH_STENCIL
    };

    /// Constructs a texture from a bitmap image
    Texture(const Image &image,
        TextureMinification _minification = TextureMinification::NearestMipmapLinear,
        TextureMagnification _magnification = TextureMagnification::Linear,
        TextureWrap _SWrap = TextureWrap::Repeat, TextureWrap _TWrap = TextureWrap::Repeat);

    /// Constructs a texture from an image file
    Texture(std::string path, Format format = Format::RGB,
        TextureMinification _minification = TextureMinification::NearestMipmapLinear,
        TextureMagnification _magnification = TextureMagnification::Linear,
        TextureWrap _SWrap = TextureWrap::Repeat, TextureWrap _TWrap = TextureWrap::Repeat);

    /// Constructs a texture from an image file
    Texture(std::string path, InternalFormat internalFormat, Format format,
        TextureMinification _minification = TextureMinification::NearestMipmapLinear,
        TextureMagnification _magnification = TextureMagnification::Linear,
        TextureWrap _SWrap = TextureWrap::Repeat, TextureWrap _TWrap = TextureWrap::Repeat);

    /// Destroys the texture
    ~Texture();
private:
    /// Loads image data into a texture
    void loadImage(const Image &image);

    /// The OpenGL texture object
    GLuint texture;

    /// The minification mode
    TextureMinification minification;

    /// The magnification mode
    TextureMagnification magnification;

    /// The wrapping mode along the S axis
    TextureWrap SWrap;

    /// The wrapping mode along the T axis
    TextureWrap TWrap;
};

/// A class that contains a bitmap image, which can be loaded into a texture
class Image {
public:
    /// Constructs an image with a pointer to a byte array and the image size
    /**
     * Remember to pad the length of each line to a multiple of 4. For
     * example, if your image is 10 pixels wide and in the RGB format,
     * your image will be 30 bytes wide, but you must add 2 extra bytes
     * at the end of each line to pad it correctly.
     * @warning You are responsible for the memory of the image data.
     * It may be freed after it is used to create a texture.
     */
    template<typename T>
    Image(glm::ivec2 _size, const T *_data, Texture::InternalFormat _internalFormat,
            Texture::Format _format) :
            size(_size), data(_data), internalFormat((GLint)_internalFormat), format((GLenum)_format), type(dataType<T>()) {

    }

    /// Constructs an image by deducing the internal format
    template<typename T>
    Image(glm::ivec2 _size, const T *_data, Texture::Format _format = Texture::Format::RGB) :
            size(_size), data(_data), internalFormat(deduceInternalFormat(_format)), format((GLenum)_format), type(dataType<T>()) {

    }

    /// The size of the image
    const glm::ivec2 size;

    /// The image data
    const GLvoid *data;

    /// The internal format of the image
    const GLint internalFormat;

    /// The format of the image
    const GLenum format;

    /// The type of the image
    const GLenum type;
private:
    /// Deduces an internal format for a pixel format
    static GLint deduceInternalFormat(Texture::Format format);

    /// Takes a template parameter and returns an OpenGL pixel type
    template<typename T>
    static constexpr GLenum dataType();
};

template<>
inline GLenum Image::dataType<unsigned char>() { return GL_UNSIGNED_BYTE; }

template<>
inline GLenum Image::dataType<char>() { return GL_BYTE; }

template<>
inline GLenum Image::dataType<unsigned short>() { return GL_UNSIGNED_SHORT; }

template<>
inline GLenum Image::dataType<short>() { return GL_SHORT; }

template<>
inline GLenum Image::dataType<unsigned int>() { return GL_UNSIGNED_INT; }

template<>
inline GLenum Image::dataType<int>() { return GL_INT; }

template<>
inline GLenum Image::dataType<float>() { return GL_FLOAT; }

} // namespace

#endif
