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
        
        functionMap["playSound"] = bind(&SunSoundObject::playSound, this, placeholders::_1);
    }
    
    void addSoundFromBuffer(SunSoundBufferStorage *_storage, string _soundName) {
        SunSound newSound;
        newSound.name = _soundName;
        
        newSound.sound.setBuffer(_storage->bufferMap[_soundName].buffer);
        
        sounds[_soundName] = newSound;
    }
    
    void playSound(SunNodeSentAction _action) {
        string soundName = *(string *)_action.parameters["soundName"];
        
        sounds[soundName].play();
    }
private:
    
};

#endif

