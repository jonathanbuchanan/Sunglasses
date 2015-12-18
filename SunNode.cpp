#include "SunNode.h"

#include "Libraries/glm/glm.hpp"

void SunNode::changeValue(SunNodeSentAction _action) {
    string targetProperty = *(string *) _action.parameters["targetProperty"];

    if (propertyMap.find(targetProperty) != propertyMap.end()) {
        if (propertyMap[targetProperty].type == SunNodePropertyTypeVec3)
            *((glm::vec3 *)propertyMap[targetProperty].pointer) = *((glm::vec3 *)_action.parameters["targetValuePointer"]);
        else if (propertyMap[targetProperty].type == SunNodePropertyTypeBool)
            *((GLboolean *) propertyMap[targetProperty].pointer) = *((GLboolean *) _action.parameters["targetValuePOinter"]);
    }
}

void SunNode::toggleBool(SunNodeSentAction _action) {
    string targetProperty = *(string *) _action.parameters["targetProperty"];

    if (propertyMap.find(targetProperty) != propertyMap.end()) {
        if (propertyMap[targetProperty].type == SunNodePropertyTypeBool)
            *((GLboolean *) propertyMap[targetProperty].pointer) = !*((GLboolean *) propertyMap[targetProperty].pointer);
    }
}

void SunNode::initializeDefaultPropertyAndFunctionMap() {
    type = "node";

    propertyMap["type"] = SunNodeProperty(&type, SunNodePropertyTypeString);

    functionMap["changeValue"] = bind(&SunNode::changeValue, this, std::placeholders::_1);
    functionMap["toggleBool"] = bind(&SunNode::toggleBool, this, std::placeholders::_1);
    functionMap["test"] = bind(&SunNode::test, this, std::placeholders::_1);
}

void SunNode::test(SunNodeSentAction _action) {
	
}

void SunNode::receiveAction(SunNodeSentAction _action) {
    parentsReady = 0;
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

    for (int i = 0; i < subNodes.size(); i++)
        subNodes[i]->parentsReady += 1;

    if (_action.recursive) {
        for (int i = 0; i < subNodes.size(); i++) {
            if (subNodes[i]->parentsReady == subNodes[i]->parents.size())
                sendAction(_action, subNodes[i]);
        }
    }
}

void SunNode::sendAction(SunNodeSentAction _action, SunNode *_receiver) {
	_action.sender = this;
    _receiver->receiveAction(_action);
}

void SunNode::sendActionToAllSubNodes(SunNodeSentAction _action) {
	_action.sender = this;
    for (int i = 0; i < subNodes.size(); ++i)
        sendAction(_action, subNodes[i]);
}

void SunNode::addSubNode(SunNode *_subNode) {
    // Add the Sub-Node
    if (find(subNodes.begin(), subNodes.end(), _subNode) == subNodes.end()) {
        subNodes.push_back(_subNode);
        _subNode->parents.push_back(this);
        _subNode->level = level + 1;
        _subNode->rootNode = rootNode;
    }
}

void SunNode::findNode(string _path, SunNode &_node) {
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

void SunNode::findNode(string _path, SunNode *&_node) {
    vector<string> levels = splitString(_path, *"/");

    GLboolean done = false;

    if (level + 1 == levels.size() && levels[level] == name) {
        _node = this;
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

void SunNode::findNodeWithName(string _name, SunNode &_node) {
    for (int i = 0; i < subNodes.size(); i++) {
        if (subNodes[i]->name == _name) {
            _node = *subNodes[i];
            break;
        } else {
            subNodes[i]->findNodeWithName(_name, _node);
        }
    }
}

void SunNode::findPointerNodeWithName(string _name, SunNode *&_node) {
    if (name == _name) {
        _node = this;
    } else {
        for (int i = 0; i < subNodes.size(); i++) {
            subNodes[i]->findPointerNodeWithName(_name, _node);
        }
    }
}

void SunNode::log() {
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

void sendAction(SunNodeSentAction _action, SunNode *_receiver) {
    _receiver->receiveAction(_action);
}
