// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/SunBase.h>

namespace sunglasses {

SunServiceManager SunBase::services = SunServiceManager();

SunBase::SunBase() { }

SunBase::SunBase(std::string n) : name(n) {

}

void SunBase::processAction(SunAction action) {
    if (actions.find(action.getAction()) != actions.end())
        actions[action.getAction()](action);
}

void sendAction(SunAction action, SunBase *base) {
    base->processAction(action);
}

} // namespace
