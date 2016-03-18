// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunAction.h"

SunAction::SunAction() { }
SunAction::SunAction(std::string a) {
	action = a;
}
SunAction::SunAction(std::string a, SunActionParameterMap p) {
	action = a;
	parameters = p;
}
SunAction::SunAction(std::string a, SunActionParameterMap p, bool r) {
	action = a;
	parameters = p;
	recursive = r;
}
