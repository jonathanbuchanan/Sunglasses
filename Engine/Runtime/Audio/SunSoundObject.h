// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
/* 
 * File:   SunSoundObject.h
 * Author: jonathan
 *
 * Created on August 1, 2015, 7:33 PM
 */

#ifndef SUNSOUNDOBJECT_H
#define	SUNSOUNDOBJECT_H

#include "SunNode.h"
#include "./SunSoundBufferStorage.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct SunSound {
    string name;
    sf::Sound sound;
    
    void play() {
        sound.play();
    }
};

class SunSoundObject : public SunNode {
public:
    SunSoundObject();
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    void addSoundFromBuffer(SunSoundBufferStorage *_storage, string _soundName, float _minimumDistance, float _attenuation);
    void playSound(SunAction action);
    
    inline map<string, SunSound> & getSounds() { return sounds; }
    inline SunSound & getSoundForString(string s) { return sounds[s]; }
    inline void addSoundForString(SunSound _sound, string s) { sounds[s] = _sound; }
private:
    map<string, SunSound> sounds;
};

#endif

