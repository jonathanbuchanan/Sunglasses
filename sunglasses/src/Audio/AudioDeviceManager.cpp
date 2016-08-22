// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Audio/AudioDeviceManager.h>

#include <AL/alut.h>

namespace sunglasses {

AudioDeviceManager::AudioDeviceManager() {
    initialize();
}

void AudioDeviceManager::initialize() {
    device = alcOpenDevice(NULL);

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    alutInit(0, NULL);
}

void AudioDeviceManager::update() {

}

} // namespace
