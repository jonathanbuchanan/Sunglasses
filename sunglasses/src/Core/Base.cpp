// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/Base.h>

namespace sunglasses {

ServiceManager Base::services = ServiceManager();

Base::Base() { }

Base::Base(std::string n) : name(n) {

}

void Base::processAction(Action action) {
    if (actions.find(action.getAction()) != actions.end())
        actions[action.getAction()](action);
}

void sendAction(Action action, Base *base) {
    base->processAction(action);
}

} // namespace
