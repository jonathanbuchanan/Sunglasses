#include "SunMusicObject.h"

SunMusicObject::SunMusicObject(string _file, string _name) {
    loadFromFile(_file);
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();
}
SunMusicObject::SunMusicObject(string _file, string _name, bool _loops) {
    loadFromFile(_file);
    setLoops(_loops);
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();
}

void SunMusicObject::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    addToFunctionMap("play", bind(&SunMusicObject::play, this, placeholders::_1));
    addToFunctionMap("pause", bind(&SunMusicObject::pause, this, placeholders::_1));
    addToFunctionMap("stop", bind(&SunMusicObject::stop, this, placeholders::_1));
}
