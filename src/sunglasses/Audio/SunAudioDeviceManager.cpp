// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunAudioDeviceManager.h"

#include <AL/alut.h>

SunAudioDeviceManager::SunAudioDeviceManager() {
    initialize();
}

void SunAudioDeviceManager::initialize() {
    device = alcOpenDevice(NULL);

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    alutInit(0, NULL);
}

void SunAudioDeviceManager::update() {

}
