// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunSoundListener.h"

SunSoundListener::SunSoundListener(glm::vec3 _position, glm::vec3 _direction) {
    setPosition(_position);
    setDirection(_direction);
}

void SunSoundListener::setPositionAndDirection() {
    sf::Listener::setPosition(position.x, position.y, position.z);
    sf::Listener::setDirection(direction.x, direction.y, direction.z);
}