// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Audio/AudioListener.h>

namespace sunglasses {

AudioListener::AudioListener(glm::vec3 _position) :
    position(_position) {

}

void AudioListener::init() {
    addAction("update", &AudioListener::update);
}

void AudioListener::update(Action action) {
    glm::vec3 velocity = glm::vec3(0.0f);

    alListener3f(AL_POSITION, position.x, position.y, position.z);
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

} // namespace
