// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/Action.h>

namespace sunglasses {

Action::Action() {
    recursive = false;
}

Action::Action(std::string a) : action(a) {
    Action();
}

Action::Action(std::string a, ActionParameterMap p) : action(a), parameters(p) {
    Action();
}

Action::Action(std::string a, ActionParameterMap p, bool r) : action(a), parameters(p), recursive(r) {
    Action();
}

} // namespace
