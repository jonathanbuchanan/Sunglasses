// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef AUDIOBUFFERRESOURCE_H
#define AUDIOBUFFERRESOURCE_H

#include <sunglasses/Extern/Resource.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <string>

namespace sunglasses {

/// A Resource subclass containing loaded audio data
class AudioBufferResource : public Resource {
public:
    /// Constructor
    AudioBufferResource(std::string _path);

    /// Initializes the buffer
    void init();

    /// Gets the OpenAL buffer
    int getBuffer() { return buffer; }
private:
    /// The OpenAL buffer
    ALuint buffer;

    /// The path to the audio file
    std::string path;
};

} // namespace

#endif
