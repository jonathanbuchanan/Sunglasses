// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Audio/SunAudioBufferResource.h>

#include <AL/alut.h>

namespace sunglasses {

SunAudioBufferResource::SunAudioBufferResource(std::string _path) : path(_path) {

}

void SunAudioBufferResource::init() {
    buffer = alutCreateBufferFromFile(path.c_str());
}

} // namespace
