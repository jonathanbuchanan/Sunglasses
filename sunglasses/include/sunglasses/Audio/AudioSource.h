// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <glm/glm.hpp>

#include <sunglasses/Audio/AudioBufferResource.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace sunglasses {

/// A class that represents a source of sound in 3D space
class AudioSource {
public:
    /// Constructor
    AudioSource(AudioBufferResource *_buffer,
        glm::vec3 _position = glm::vec3(0.0f),
        float _pitch = 1.0f,
        float _gain = 1.0f
    );

    /// Initializes the audio source
    void init();

    /// Plays the sound
    void play();
private:
    /// The position of the source
    glm::vec3 position;

    /// The pitch of the sound (speed of the sound)
    float pitch;
    
    /// The gain of the sound
    float gain;

    /// The audio buffer
    AudioBufferResource *buffer;

    /// The audio source
    ALuint source;
};

} // namespace

#endif
