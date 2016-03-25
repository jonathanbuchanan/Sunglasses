// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNSOUNDBUFFERSTORAGE_H
#define    SUNSOUNDBUFFERSTORAGE_H

#include <vector>
#include <map>

#include <SFML/Audio.hpp>

struct SunSoundBuffer {
    std::string name;
    sf::SoundBuffer buffer;
};

class SunSoundBufferStorage {
public:
    void loadSoundFromFileWithName(std::string _file, std::string _name);

    inline std::map<std::string, SunSoundBuffer> & getBufferMap() { return bufferMap; }
    inline SunSoundBuffer & getBufferForString(std::string s) { return bufferMap[s]; }
    inline void addBufferForString(SunSoundBuffer _buffer, std::string s) { bufferMap[s] = _buffer; }
private:
    std::map<std::string, SunSoundBuffer> bufferMap;
};

#endif
