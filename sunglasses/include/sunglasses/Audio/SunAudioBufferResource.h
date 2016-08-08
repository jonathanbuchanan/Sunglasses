// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNAUDIOBUFFERRESOURCE_H
#define SUNAUDIOBUFFERRESOURCE_H

#include <sunglasses/Extern/SunResource.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <string>

namespace sunglasses {

/// A SunResource subclass containing loaded audio data
class SunAudioBufferResource : public SunResource {
public:
    /// Constructor
    SunAudioBufferResource(std::string _path);

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
