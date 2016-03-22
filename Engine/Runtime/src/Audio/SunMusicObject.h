// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNMUSICOBJECT_H
#define	SUNMUSICOBJECT_H

#include "../Core/SunNode.h"
#include <SFML/Audio.hpp>

class SunMusicObject : public SunNode {
public:

    SunMusicObject(std::string _file, std::string _name);
    SunMusicObject(std::string _file, std::string _name, bool _loops);

    virtual void init();

    inline void setLoops(bool _loops) { music.setLoop(_loops); }
    inline void loadFromFile(std::string _file) { music.openFromFile(_file); }
    inline void play(SunAction action) { music.play(); }
    inline void pause(SunAction action) { music.pause(); }
    inline void stop(SunAction action) {  music.stop(); }
    inline sf::Music & getMusic() { return music; }
private:
    sf::Music music;
};

#endif
