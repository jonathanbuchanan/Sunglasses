/* 
 * File:   SunSoundBufferStorage.h
 * Author: jonathan
 *
 * Created on August 4, 2015, 7:55 PM
 */

#ifndef SUNSOUNDBUFFERSTORAGE_H
#define	SUNSOUNDBUFFERSTORAGE_H

#include <vector>
#include <map>

using namespace std;

#include <SFML/Audio.hpp>

struct SunSoundBuffer {
    string name;
    sf::SoundBuffer buffer;
};

class SunSoundBufferStorage {
public:
    void loadSoundFromFileWithName(string _file, string _name);
    
    inline map<string, SunSoundBuffer> & getBufferMap() { return bufferMap; }
    inline SunSoundBuffer & getBufferForString(string s) { return bufferMap[s]; }
    inline void addBufferForString(SunSoundBuffer _buffer, string s) { bufferMap[s] = _buffer; }
private:
    map<string, SunSoundBuffer> bufferMap;
};

#endif

