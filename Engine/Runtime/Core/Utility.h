// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_Utility_h
#define Sunglasses_Utility_h

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#include "Graphics/SunShader.h"

typedef map<string, SunShader>::iterator ShaderMapIterator;

extern vector<string> splitString(const string &_string, const char &_delimeter);

#endif
