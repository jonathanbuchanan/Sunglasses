// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunButtonState.h"

bool isPressed(SunButtonState _state) {
    if (_state == SunButtonStatePressed || _state == SunButtonStatePressedEdge)
        return true;
    return false;
}
