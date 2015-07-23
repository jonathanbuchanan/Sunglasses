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
    SunNodePropertyTypeString,
    SunNodePropertyTypeFloat,
    SunNodePropertyTypeVec2,
    SunNodePropertyTypeVec3,
    SunNodePropertyTypeNode
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
    
    bool isIntOrFloat() {
        if (type == SunNodePropertyTypeInt || type == SunNodePropertyTypeFloat)
            return true;
        return false;
    }
    
};

typedef void * SunNodeSentActionParameter;

enum SunNodeSentActionConditionType {
    SunNodeSentActionConditionTypeLessThan,
    SunNodeSentActionConditionTypeGreaterThan,
    SunNodeSentActionConditionTypeEqualTo,
    SunNodeSentActionConditionTypeTrue,
    SunNodeSentActionConditionTypeFalse
};

struct SunNodeSentActionCondition {
    SunNodeSentActionConditionType conditionType;
    string nodeProperty;
    SunNodeProperty comparativeProperty;
    
    SunNodeSentActionCondition() {
        
    }
    
    bool evaluate(SunNodeProperty propertyOne) {
        switch (conditionType) {
            case SunNodeSentActionConditionTypeLessThan:
                if (propertyOne.isIntOrFloat() == true && comparativeProperty.isIntOrFloat()) {
                    if (*(float *) propertyOne.pointer <= *(float *)comparativeProperty.pointer)
                        return true;
                }
                return false;
                break;
            case SunNodeSentActionConditionTypeGreaterThan:
                if (propertyOne.isIntOrFloat() == true && comparativeProperty.isIntOrFloat()) {
                    if (*(float *) propertyOne.pointer >= *(float *)comparativeProperty.pointer)
                        return true;
                }
                return false;
                break;
            case SunNodeSentActionConditionTypeEqualTo:
                if (propertyOne.isIntOrFloat() == true && comparativeProperty.isIntOrFloat()) {
                    if (*(float *)propertyOne.pointer == *(float *)comparativeProperty.pointer)
                        return true;
                } else if (propertyOne.type == SunNodePropertyTypeString && comparativeProperty.type == SunNodePropertyTypeString) {
                    if (*(string *)propertyOne.pointer == *(string *)comparativeProperty.pointer)
                        return true;
                }
                
                return false;
                break;
            case SunNodeSentActionConditionTypeTrue:
                if (propertyOne.type == SunNodePropertyTypeBool)
                    if (*(bool *)propertyOne.pointer == true)
                        return true;
                return false;
                break;
            case SunNodeSentActionConditionTypeFalse:
                if (propertyOne.type == SunNodePropertyTypeBool)
                    if (*(bool *)propertyOne.pointer == false)
                        return true;
                return false;
                break;
        }
        return false;
    }
    
};

struct SunNodeSentAction {
    map<string, void *> properties;
    map<string, SunNodeSentActionParameter> parameters;
    vector<SunNodeSentActionCondition> conditions;
    string action;
    GLboolean recursive = false;
};

typedef function<void(SunNodeSentAction)>SunNodeFunctionPointer;

class SunNode {
public:
    map<string, SunNodeProperty> propertyMap;
    map<string, SunNodeFunctionPointer> functionMap;
    vector<SunNode *> subNodes;
    vector<SunNode *> parents;
    int level;
    string name;
    string type;
    
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
        type = "node";
        
        propertyMap["type"] = SunNodeProperty(&type, SunNodePropertyTypeString);
        
        functionMap["changeValue"] = bind(&SunNode::changeValue, this, std::placeholders::_1);
        functionMap["toggleBool"] = bind(&SunNode::toggleBool, this, std::placeholders::_1);
    }
    
    virtual void receiveAction(SunNodeSentAction _action) {
        if (functionMap.find(_action.action) != functionMap.end()) {
            int conditionsMet = 0;
            for (int i = 0; i < _action.conditions.size(); i++) {
                bool condition = _action.conditions[i].evaluate(propertyMap[_action.conditions[i].nodeProperty]);
                if (condition == true) {
                    conditionsMet += 1;
                }
            }
        
            if (conditionsMet == _action.conditions.size()) {
                SunNodeFunctionPointer function = functionMap[_action.action];
                function(_action);
            }
        }
        
        //if (_action.recursive)
        //    sendActionToAllSubNodes(_action);
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
        if (find(subNodes.begin(), subNodes.end(), _subNode) == subNodes.end()) {
            subNodes.push_back(_subNode);
            _subNode->parents.push_back(this);
            _subNode->level = level + 1;
            _subNode->rootNode = rootNode;
        }
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
    
    virtual void findNodeWithName(string _name, SunNode &_node) {
        for (int i = 0; i < subNodes.size(); i++) {
            if (subNodes[i]->name == _name) {
                _node = *subNodes[i];
                break;
            } else {
                subNodes[i]->findNodeWithName(_name, _node);
            }
        }
    }
    
    virtual void findPointerNodeWithName(string _name, SunNode *&_node) {
        if (name == _name) {
            _node = this;
        } else {
            for (int i = 0; i < subNodes.size(); i++) {
                subNodes[i]->findPointerNodeWithName(_name, _node);
            }
        }
    }
    
    virtual void log() {
        string log;
        
        for (int i = 0; i < level; i++) {
            log += "    ";
        }
        
        log += name;
        log += "\n";
        
        cout << log << flush;
        
        for (int i = 0; i < subNodes.size(); i++)
            subNodes[i]->log();
    }
    
private:
    
};

void sendAction(SunNodeSentAction _action, SunNode *_receiver) {
        _receiver->receiveAction(_action);
}

#endif
