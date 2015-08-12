//
//  SunButtonState.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/30/15.
//
//

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
