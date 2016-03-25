// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunNode.h"

SunNode::SunNode() {
    parentsReady = 0;
    level = 0;
}

SunNode::SunNode(std::string _tag) : tags({_tag}) {
    SunNode();
}

SunNode::SunNode(std::vector<std::string> _tags) : tags(_tags) {
    SunNode();
}

void SunNode::init() {

}

void SunNode::processAction(SunAction action) {
    if (action.parameterExists("tag") && ignoreTags == false) {
        if (tagPresent(action.getParameter<std::string>("tag")))
            SunBase::processAction(action);
    } else
        SunBase::processAction(action);
    if (action.getRecursive() == true)
        sendActionToAllSubNodes(action);
}

bool SunNode::tagPresent(std::string t) {
    return (std::find(tags.begin(), tags.end(), t) != tags.end()) ? true : false;
}

void SunNode::sendActionToAllSubNodes(SunAction action) {
    for (size_t i = 0; i < subNodes.size(); ++i)
        sendAction(action, subNodes[i]);
}

void SunNode::addSubNode(SunNode *_subNode) {
    // Add the Sub-Node
    if (find(subNodes.begin(), subNodes.end(), _subNode) == subNodes.end()) {
        subNodes.push_back(_subNode);
        _subNode->parents.push_back(this);
        _subNode->level = level + 1;
    }
}

void SunNode::findNode(std::string _path, SunNode &_node) {
    /*vector<string> levels = splitString(_path, *"/");

    GLboolean done = false;

    if (level + 1 == levels.size() && levels[level] == getName()) {
        _node = *this;
        done = true;
    }

    if (!done) {
        if (levels[level] == getName() || level == 0) {
            for (int i = 0; i < subNodes.size(); i++) {
                subNodes[i]->findNode(_path, _node);
            }
        }
    }*/
}

void SunNode::findNode(std::string _path, SunNode *&_node) {
    /*vector<string> levels = splitString(_path, *"/");

    GLboolean done = false;

    if (level + 1 == levels.size() && levels[level] == getName()) {
        _node = this;
        done = true;
    }

    if (!done) {
        if (levels[level] == getName() || level == 0) {
            for (int i = 0; i < subNodes.size(); i++) {
                subNodes[i]->findNode(_path, _node);
            }
        }
    }*/
}

void SunNode::findNodeWithName(std::string _name, SunNode &_node) {
    for (size_t i = 0; i < subNodes.size(); i++) {
        if (subNodes[i]->getName() == _name) {
            _node = *subNodes[i];
            break;
        } else {
            subNodes[i]->findNodeWithName(_name, _node);
        }
    }
}

void SunNode::findPointerNodeWithName(std::string _name, SunNode *&_node) {
    if (getName() == _name) {
        _node = this;
    } else {
        for (size_t i = 0; i < subNodes.size(); i++) {
            subNodes[i]->findPointerNodeWithName(_name, _node);
        }
    }
}

void SunNode::recursiveDeleteSubnode(const SunNode *node) {
    for (size_t i = 0; i < subNodes.size(); i++) {
        if (subNodes[i] == node)
            subNodes.erase(subNodes.begin() + i);
        else
            subNodes[i]->recursiveDeleteSubnode(node);
    }
}
