/* 
 * File:   SunMusicObject.h
 * Author: jonathan
 *
 * Created on August 5, 2015, 12:23 AM
 */

#ifndef SUNMUSICOBJECT_H
#define	SUNMUSICOBJECT_H

#include "../SunNode.h"
#include <SFML/Audio.hpp>

class SunMusicObject : public SunNode {
public:
    
    SunMusicObject(string _file, string _name);
    SunMusicObject(string _file, string _name, bool _loops);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    
    inline void setLoops(bool _loops) { music.setLoop(_loops); }
    inline void loadFromFile(string _file) { music.openFromFile(_file); }
    inline void play(SunNodeSentAction _action) { music.play(); }
    inline void pause(SunNodeSentAction _action) { music.pause(); }
    inline void stop(SunNodeSentAction _action) {  music.stop(); }
    inline sf::Music & getMusic() { return music; }
private:
    sf::Music music;
};

#endif

