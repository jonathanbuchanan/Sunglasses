// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Audio/AudioSource.h>

namespace sunglasses {

AudioSource::AudioSource(AudioBufferResource *_buffer,
        glm::vec3 _position,
        float _pitch,
        float _gain) :
    position(_position), pitch(_pitch), gain(_gain), buffer(_buffer) {

}

void AudioSource::init() {
    alGenSources(1, &source);

    alSourcei(source, AL_BUFFER, buffer->getBuffer());
}

void AudioSource::play() {
    alSourcePlay(source);
}

} // namespace
