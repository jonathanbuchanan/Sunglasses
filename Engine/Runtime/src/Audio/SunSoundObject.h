// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNSOUNDOBJECT_H
#define	SUNSOUNDOBJECT_H

#include <map>
#include <string>

#include "../Core/SunNode.h"
#include "SunSoundBufferStorage.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct SunSound {
    std::string name;
    sf::Sound sound;

    void play() {
        sound.play();
    }
};

class SunSoundObject : public SunNode {
public:
    SunSoundObject();

    virtual void init();
    void addSoundFromBuffer(SunSoundBufferStorage *_storage, std::string _soundName, float _minimumDistance, float _attenuation);
    void playSound(SunAction action);

    std::map<std::string, SunSound> & getSounds() { return sounds; }
    SunSound & getSoundForString(std::string s) { return sounds[s]; }
    void addSoundForString(SunSound _sound, std::string s) { sounds[s] = _sound; }
private:
    std::map<std::string, SunSound> sounds;
};

#endif
