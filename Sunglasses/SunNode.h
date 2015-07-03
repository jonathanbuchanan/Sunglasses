//
//  SunNode.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 7/2/15.
//
//

#ifndef Sunglasses_SunNode_h
#define Sunglasses_SunNode_h

using namespace std;

#include <map>
#include <functional>

#include "Utility.h"

class SunNode;

// Definition of SunNodePropertyPointer
typedef void * SunNodePropertyPointer;

// Definition of SunNodePropertyType
enum SunNodePropertyType {
    SunNodePropertyTypeBool,
    SunNodePropertyTypeInt,
    SunNodePropertyTypeFloat,
    SunNodePropertyTypeVec2,
    SunNodePropertyTypeVec3
};

// Definition of SunNodeProperty
struct SunNodeProperty {
    SunNodePropertyPointer pointer;
    SunNodePropertyType type;
    
    SunNodeProperty() {
        
    }
    
    SunNodeProperty(SunNodePropertyPointer _pointer, SunNodePropertyType _type) {
        pointer = _pointer;
        type = _type;
    }
    
};

typedef void * SunNodeSentActionParameter;

struct SunNodeSentAction {
    map<string, SunNodeSentActionParameter> parameters;
    string action;
};

typedef function<void(SunNodeSentAction)>SunNodeFunctionPointer;

class SunNode {
public:
    map<string, SunNodeProperty> propertyMap;
    map<string, SunNodeFunctionPointer> functionMap;
    vector<SunNode *> subNodes;
    SunNode *parent;
    int level = 0;
    string name;
    
    SunNode *rootNode;
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        
    }
    
    virtual void receiveAction(SunNodeSentAction _action) {
        if (functionMap.find(_action.action) != functionMap.end()) {
            SunNodeFunctionPointer function = functionMap[_action.action];
            function(_action);
        }
    }
    
    virtual void sendAction(SunNodeSentAction _action, SunNode *_receiver) {
        _receiver->receiveAction(_action);
    }
    
    virtual void addSubNode(SunNode *_subNode) {
        // Add the Sub-Node
        subNodes.push_back(_subNode);
        _subNode->parent = this;
        _subNode->level = level + 1;
    }
    
    virtual void findNode(string _path, vector<string> _levels, SunNode &_node) {
        vector<string> levels = _levels;
        
        if (levels.size() == 0) {
            levels = splitString(_path, *"/");
        }
        
        GLboolean done = false;
        
        if (level + 1 == _levels.size() && levels[level] == name) {
            _node = *this;
            done = true;
        }
        
        if (!done) {
            if (levels[level] == name || level == 0) {
                for (int i = 0; i < subNodes.size(); i++) {
                    subNodes[i]->findNode(_path, _levels, _node);
                }
            }
        }
    }
    
private:
    
};

#endif
