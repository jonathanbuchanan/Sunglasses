/* 
 * File:   SunSoundObject.h
 * Author: jonathan
 *
 * Created on August 1, 2015, 7:33 PM
 */

#ifndef SUNSOUNDOBJECT_H
#define	SUNSOUNDOBJECT_H
#include "../SunNode.h"
#include "./SunSoundBufferStorage.h"

struct SunSound {
    string name;
    sf::Sound sound;
    
    void play() {
        sound.play();
    }
};

class SunSoundObject : public SunNode {
public:
    map<string, SunSound> sounds;
    
    SunSoundObject() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        addToFunctionMap("playSound", bind(&SunSoundObject::playSound, this, placeholders::_1));
    }
    
    void addSoundFromBuffer(SunSoundBufferStorage *_storage, string _soundName, float _minimumDistance, float _attenuation) {
        SunSound newSound;
        newSound.name = _soundName;
        
        newSound.sound.setBuffer(_storage->getBufferForString(_soundName).buffer);
        newSound.sound.setMinDistance(_minimumDistance);
        newSound.sound.setAttenuation(_attenuation);
        
        sounds[_soundName] = newSound;
    }
    
    void playSound(SunNodeSentAction _action) {
        string soundName = *(string *)_action.parameters["soundName"];  
        
        if (_action.parameters.find("position") != _action.parameters.end()) {
            glm::vec3 position = *(glm::vec3 *)_action.parameters["position"];
            
            sounds[soundName].sound.setPosition(position.x, position.y, position.z);
        }
        
        sounds[soundName].play();
    }
    
private:
    
};

#endif

