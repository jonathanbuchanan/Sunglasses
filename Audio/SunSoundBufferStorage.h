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
    map<string, SunSoundBuffer> bufferMap;
    
    void loadSoundFromFileWithName(string _file, string _name) {
        SunSoundBuffer newBuffer;
        
        newBuffer.name = _name;
        newBuffer.buffer.loadFromFile(_file);
        
        bufferMap[_name] = newBuffer;
    }
private:
    
};

#endif

