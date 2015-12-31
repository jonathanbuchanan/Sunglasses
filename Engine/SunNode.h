// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunNode_h
#define Sunglasses_SunNode_h

#include <vector>
#include <string>
#include <map>
#include <GL/glew.h>
#include "./Utility.h"
#include <functional>

using namespace std;

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

typedef map<string, void *>::iterator SunNodeSentActionPropertyMapIterator;

struct SunNodeSentAction {
    map<string, void *> properties;
    map<string, SunNodeSentActionParameter> parameters;
    vector<SunNodeSentActionCondition> conditions;
    SunNode *sender;
    string action;
    GLboolean recursive = false;
    GLboolean inOrder = false;
};

typedef function<void(SunNodeSentAction)>SunNodeFunctionPointer;

class SunNode {
public:
    SunNode() {
        
    }
    
    virtual void changeValue(SunNodeSentAction _action);
    
    virtual void toggleBool(SunNodeSentAction _action);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    
    virtual void receiveAction(SunNodeSentAction _action);
    
    virtual void sendAction(SunNodeSentAction _action, SunNode *_receiver);
    
    virtual void sendActionToAllSubNodes(SunNodeSentAction _action);
    
    virtual void test(SunNodeSentAction _action);
    
    virtual void addSubNode(SunNode *_subNode);
    
    virtual void findNode(string _path, SunNode &_node);
    
    virtual void findNode(string _path, SunNode *&_node);
    
    virtual void findNodeWithName(string _name, SunNode &_node);
    
    virtual void findPointerNodeWithName(string _name, SunNode *&_node);
    
    virtual void log();
    
    inline map<string, SunNodeProperty> & getPropertyMap() { return propertyMap; }
    inline void addToPropertyMap(string propertyName, SunNodeProperty property) { propertyMap[propertyName] = property; }
    
    inline map<string, SunNodeFunctionPointer> & getFunctionMap() { return functionMap; }
    inline void addToFunctionMap(string functionName, SunNodeFunctionPointer function) { functionMap[functionName] = function; }
    
    inline vector<SunNode *> & getSubNodes() { return subNodes; }
    inline int getSubNodesSize() { return subNodes.size(); }
    inline SunNode * getSubNodeAtIndex(int i) { return subNodes[i]; }
    
    inline int getLevel() { return level; }
    inline void setLevel(int _level) { level = _level; }
    
    inline string getName() { return name; }
    inline void setName(string _name) { name = _name; }
    
    inline string getType() { return type; }
    inline void setType(string _type) { type = _type; }
    
    inline SunNode * getRootNode() { return rootNode; }
    inline void setRootNode(SunNode *_rootNode) { rootNode = _rootNode; }
    
    inline vector<SunNode *> & getParents() { return parents; }
    inline int getParentsSize() { return parents.size(); }
    inline SunNode * getParentAtIndex(int i) { return parents[i]; }
private:
    map<string, SunNodeProperty> propertyMap;
    map<string, SunNodeFunctionPointer> functionMap;
    GLuint parentsReady = 0;
    vector<SunNode *> subNodes;
    vector<SunNode *> parents;
    int level = 0;
    string name;
    string type;
    
    SunNode *rootNode;
};

extern void sendAction(SunNodeSentAction _action, SunNode *_receiver);

#endif
