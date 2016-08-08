// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Audio/SunAudioListener.h>

namespace sunglasses {

SunAudioListener::SunAudioListener(glm::vec3 _position) :
    position(_position) {

}

void SunAudioListener::init() {
    addAction("update", &SunAudioListener::update);
}

void SunAudioListener::update(SunAction action) {
    glm::vec3 velocity = glm::vec3(0.0f);

    alListener3f(AL_POSITION, position.x, position.y, position.z);
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

} // namespace
