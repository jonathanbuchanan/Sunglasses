// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Audio/AudioBufferResource.h>

#include <AL/alut.h>

namespace sunglasses {

AudioBufferResource::AudioBufferResource(std::string _path) : path(_path) {

}

void AudioBufferResource::init() {
    buffer = alutCreateBufferFromFile(path.c_str());
}

} // namespace
