//
//  Utility.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/24/15.
//
//

#ifndef Sunglasses_Utility_h
#define Sunglasses_Utility_h

using namespace std;

#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "./Graphics/Shaders/SunShader.h"

typedef map<string, SunShader>::iterator ShaderMapIterator;

vector<string> splitString(const string &_string, const char &_delimeter) {
    typedef string::const_iterator Iterator;
    Iterator beginning = _string.begin();
    vector<string> tokens;
    
    while (beginning != _string.end()) {
        Iterator temporary = find(beginning, _string.end(), _delimeter);
        tokens.push_back(std::string(beginning, temporary));
        beginning = temporary;
        while ((beginning != _string.end()) && (*beginning == _delimeter))
            beginning++;
    }
    
    return tokens;
}

#endif
