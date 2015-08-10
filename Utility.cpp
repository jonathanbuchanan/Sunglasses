#include "Utility.h"

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
