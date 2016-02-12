// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunBase.h"

SunBase::SunBase() { }

SunBase::SunBase(std::string n) {
    name = n;
}

void SunBase::init() {
    
}

template<typename T>
void SunBase::addAction(std::string function, T &&t) {
	functions[function] = std::bind(t, this, std::placeholders::_1);
}

void SunBase::processAction(SunAction action) {
	functions[action.getAction()](action);
}

extern void sendAction(SunAction action, SunBase *base) {
	base->processAction(action);
}
