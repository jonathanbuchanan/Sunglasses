//
//  SunButtonState.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/30/15.
//
//

#ifndef Sunglasses_SunButtonState_h
#define Sunglasses_SunButtonState_h

enum SunButtonState {
    SunButtonStateReleased = 0,
    SunButtonStatePressedEdge,
    SunButtonStatePressed,
};

bool isPressed(SunButtonState _state) {
    if (_state == SunButtonStatePressed || _state == SunButtonStatePressedEdge)
        return true;
    return false;
}

#endif
