// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunMusicObject.h"

SunMusicObject::SunMusicObject(string _file, string _name) {
    loadFromFile(_file);
    setName(_name); 
}
SunMusicObject::SunMusicObject(string _file, string _name, bool _loops) {
    loadFromFile(_file);
    setLoops(_loops);
    setName(_name); 
}

void SunMusicObject::init() { 
	addAction("play", &SunMusicObject::play);
	addAction("pause", &SunMusicObject::pause);
	addAction("stop", &SunMusicObject::stop); 
}
