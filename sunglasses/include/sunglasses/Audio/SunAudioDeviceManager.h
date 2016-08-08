// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNAUDIODEVICEMANAGER_H
#define SUNAUDIODEVICEMANAGER_H

#include <sunglasses/Core/SunService.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace sunglasses {

/// A service that manages the audio context and playing music.
class SunAudioDeviceManager : public SunService {
public:
    /// Constructor
    SunAudioDeviceManager();

    /// Initializes the audio device manager
    void initialize();

    /// Updates the audio device manager
    virtual void update();
private:
    /// The audio device
    ALCdevice *device;

    /// The audio context
    ALCcontext *context;
};

} // namespace

#endif
