// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunBase.h"

std::map<std::string, SunService *> SunBase::services;

SunBase::SunBase() { }

SunBase::SunBase(std::string n) {
    name = n;
}

void SunBase::init() {
    
}

void SunBase::processAction(SunAction action) {
	functions[action.getAction()](action);
}

void sendAction(SunAction action, SunBase *base) {
	base->processAction(action);
}
