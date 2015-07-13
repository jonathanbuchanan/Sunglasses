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

#include "./Utility.h"

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
    map<string, void *> properties;
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
    int level;
    string name;
    
    SunNode *rootNode;
    
    SunNode() {
        level = 0;
    }
    
    virtual void changeValue(SunNodeSentAction _action) {
        string targetProperty = *(string *)_action.parameters["targetProperty"];
        
        if (propertyMap.find(targetProperty) != propertyMap.end()) {
            if (propertyMap[targetProperty].type == SunNodePropertyTypeVec3)
                *((glm::vec3 *)propertyMap[targetProperty].pointer) = *((glm::vec3 *)_action.parameters["targetValuePointer"]);
            else if (propertyMap[targetProperty].type == SunNodePropertyTypeBool)
                *((GLboolean *)propertyMap[targetProperty].pointer) = *((GLboolean *)_action.parameters["targetValuePOinter"]);
        }
    }
    
    virtual void toggleBool(SunNodeSentAction _action) {
        string targetProperty = *(string *)_action.parameters["targetProperty"];
        
        if (propertyMap.find(targetProperty) != propertyMap.end()) {
            if (propertyMap[targetProperty].type == SunNodePropertyTypeBool)
                *((GLboolean *)propertyMap[targetProperty].pointer) = !*((GLboolean *)propertyMap[targetProperty].pointer);
        }
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        functionMap["changeValue"] = bind(&SunNode::changeValue, this, std::placeholders::_1);
        functionMap["toggleBool"] = bind(&SunNode::toggleBool, this, std::placeholders::_1);
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
    
    virtual void sendActionToAllSubNodes(SunNodeSentAction _action) {
        for (int i = 0; i < subNodes.size(); ++i)
            sendAction(_action, subNodes[i]);
    }
    
    virtual void addSubNode(SunNode *_subNode) {
        // Add the Sub-Node
        subNodes.push_back(_subNode);
        _subNode->parent = this;
        _subNode->level = level + 1;
        _subNode->rootNode = rootNode;
    }
    
    virtual void findNode(string _path, SunNode &_node) {
        vector<string> levels = splitString(_path, *"/");
        
        GLboolean done = false;
        
        if (level + 1 == levels.size() && levels[level] == name) {
            _node = *this;
            done = true;
        }
        
        if (!done) {
            if (levels[level] == name || level == 0) {
                for (int i = 0; i < subNodes.size(); i++) {
                    subNodes[i]->findNode(_path, _node);
                }
            }
        }
    }
    
private:
    
};

#endif
