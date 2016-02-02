#ifndef GUIACTION_H
#define GUIACTION_H

#include <functional>
#include <string>

#include "SunNode.h"

typedef std::function<void(SunNode *)> SunGUIActionFunction;

struct SunGUIAction {
    SunGUIAction() { }
    SunGUIAction(string n, SunGUIActionFunction f) { name = n, function = f; }
    
    string name;
    SunGUIActionFunction function;
    
    void run(SunNode *node);
};

#endif