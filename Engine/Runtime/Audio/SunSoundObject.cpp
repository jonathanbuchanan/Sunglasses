// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunSoundObject.h"

SunSoundObject::SunSoundObject() {
    initializeDefaultPropertyAndFunctionMap();
}

void SunSoundObject::initializeDefaultPropertyAndFunctionMap() {
    //SunNode::initializeDefaultPropertyAndFunctionMap();
	addAction("playSound", &SunSoundObject::playSound); 
}

void SunSoundObject::addSoundFromBuffer(SunSoundBufferStorage* _storage, string _soundName, float _minimumDistance, float _attenuation) {
    SunSound newSound;
    newSound.name = _soundName;

    newSound.sound.setBuffer(_storage->getBufferForString(_soundName).buffer);
    newSound.sound.setMinDistance(_minimumDistance);
    newSound.sound.setAttenuation(_attenuation);

    sounds[_soundName] = newSound;
}

void SunSoundObject::playSound(SunAction action) {
    string soundName = *(string *)action.getParameter("soundName");  
        
        if (action.parameterExists("position")) {
            glm::vec3 position = *(glm::vec3 *)action.getParameter("position");
            
            sounds[soundName].sound.setPosition(position.x, position.y, position.z);
        }
        
        sounds[soundName].play();
}
