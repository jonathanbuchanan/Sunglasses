//
//  Utility.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/24/15.
//
//

#ifndef Sunglasses_Utility_h
#define Sunglasses_Utility_h

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#include "./Graphics/Shaders/SunShader.h"

typedef map<string, SunShader>::iterator ShaderMapIterator;

extern vector<string> splitString(const string &_string, const char &_delimeter);

#endif
