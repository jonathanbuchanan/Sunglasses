/* 
 * File:   SunMusicObject.h
 * Author: jonathan
 *
 * Created on August 5, 2015, 12:23 AM
 */

#ifndef SUNMUSICOBJECT_H
#define	SUNMUSICOBJECT_H

using namespace std;

#include "../SunNode.h"
#include <SFML/Audio.hpp>

class SunMusicObject : public SunNode {
public:
    sf::Music music;
    
    SunMusicObject(string _file, string _name) {
        loadFromFile(_file);
        setName(_name);
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunMusicObject(string _file, string _name, bool _loops) {
        loadFromFile(_file);
        setLoops(_loops);
        setName(_name);
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        addToFunctionMap("play", bind(&SunMusicObject::play, this, placeholders::_1));
        addToFunctionMap("pause", bind(&SunMusicObject::pause, this, placeholders::_1));
        addToFunctionMap("stop", bind(&SunMusicObject::stop, this, placeholders::_1));
    }
    
    void setLoops(bool _loops) {
        music.setLoop(_loops);
    }
    
    void loadFromFile(string _file) {
        music.openFromFile(_file);
    }
    
    void play(SunNodeSentAction _action) {
        music.play();
    }
    
    void pause(SunNodeSentAction _action) {
        music.pause();
    }
    
    void stop(SunNodeSentAction _action) {
        music.stop();
    }
    
private:
    
};

#endif

