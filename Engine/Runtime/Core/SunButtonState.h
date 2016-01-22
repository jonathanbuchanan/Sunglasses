// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunButtonState_h
#define Sunglasses_SunButtonState_h

// Definition of SunButtonState

enum SunButtonState {
    SunButtonStateReleased = 0,
    SunButtonStatePressedEdge,
    SunButtonStatePressed,
};

// Convenience function to check if the state is pressed

extern bool isPressed(SunButtonState _state);

#endif
