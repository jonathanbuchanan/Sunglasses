// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunSoundBufferStorage.h"

void SunSoundBufferStorage::loadSoundFromFileWithName(std::string _file, std::string _name) {
    SunSoundBuffer newBuffer;

    newBuffer.name = _name;
    newBuffer.buffer.loadFromFile(_file);

    bufferMap[_name] = newBuffer;
}
