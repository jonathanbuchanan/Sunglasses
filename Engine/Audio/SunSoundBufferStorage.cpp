#include "SunSoundBufferStorage.h"

void SunSoundBufferStorage::loadSoundFromFileWithName(string _file, string _name) {
    SunSoundBuffer newBuffer;

    newBuffer.name = _name;
    newBuffer.buffer.loadFromFile(_file);

    bufferMap[_name] = newBuffer;
}