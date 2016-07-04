// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNAUDIOLISTENER_H
#define SUNAUDIOLISTENER_H

#include "../Core/SunNode.h"

#include <glm/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>

/// A node that represents an audio listener
class SunAudioListener : public SunNode {
public:
    SunAudioListener(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f));

    void init();

    void update(SunAction action);
private:
    glm::vec3 position;
};

#endif
