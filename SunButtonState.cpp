#include "SunButtonState.h"

bool isPressed(SunButtonState _state) {
    if (_state == SunButtonStatePressed || _state == SunButtonStatePressedEdge)
        return true;
    return false;
}
