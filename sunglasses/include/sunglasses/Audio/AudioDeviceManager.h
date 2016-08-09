// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef AUDIODEVICEMANAGER_H
#define AUDIODEVICEMANAGER_H

#include <sunglasses/Core/Service.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace sunglasses {

/// A service that manages the audio context and playing music.
class AudioDeviceManager : public Service {
public:
    /// Constructor
    AudioDeviceManager();

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
