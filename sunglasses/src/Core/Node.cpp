// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/SunNode.h>

#include <iostream>

namespace sunglasses {

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
    if (action.parameterExists("exclude")) {
        if (action.getParameterPointer<SunNode>("exclude") != this) {
            if (action.parameterExists("tag") && ignoreTags == false) {
                if (tagPresent(action.getParameter<std::string>("tag")))
                    SunBase::processAction(action);
            } else
                SunBase::processAction(action);
            if (action.getRecursive() == true)
                sendActionToAllSubNodes(action);
        }
    } else {
        if (action.parameterExists("tag") && ignoreTags == false) {
            if (tagPresent(action.getParameter<std::string>("tag")))
                SunBase::processAction(action);
        } else
            SunBase::processAction(action);
        if (action.getRecursive() == true)
            sendActionToAllSubNodes(action);
    }
}

bool SunNode::tagPresent(std::string t) {
    return (std::find(tags.begin(), tags.end(), t) != tags.end()) ? true : false;
}

void SunNode::sendActionToAllSubNodes(SunAction action) {
    for (size_t i = 0; i < subNodes.size(); ++i)
        subNodes[i]->processAction(action, false);
    if (action.getRecursive())
        for (size_t i = 0; i < subNodes.size(); ++i)
            subNodes[i]->sendActionToAllSubNodes(action);
}

void SunNode::addSubNode(SunNode *_subNode) {
    if (find(subNodes.begin(), subNodes.end(), std::shared_ptr<SunNode>(_subNode)) == subNodes.end()) {
        subNodes.push_back(std::shared_ptr<SunNode>(_subNode));
        _subNode->parents.push_back(this);
        _subNode->level = level + 1;
    }
}

void SunNode::addSubNode(const std::shared_ptr<SunNode> &_subNode) {
    if (find(subNodes.begin(), subNodes.end(), _subNode) == subNodes.end()) {
        subNodes.push_back(std::shared_ptr<SunNode>(_subNode));
        _subNode->parents.push_back(this);
        _subNode->level = level + 1;
    }
}

void SunNode::recursiveDeleteSubnode(SunNode *_node) {
    std::shared_ptr<SunNode> node = std::shared_ptr<SunNode>(_node);
    for (size_t i = 0; i < subNodes.size(); i++) {
        if (subNodes[i] == node)
            subNodes.erase(subNodes.begin() + i);
        else
            subNodes[i]->recursiveDeleteSubnode(_node);
    }
}

void SunNode::processAction(SunAction action, bool recursive) {
    if (action.parameterExists("exclude")) {
        if (action.getParameterPointer<SunNode>("exclude") != this) {
            if (action.parameterExists("tag") && ignoreTags == false) {
                if (tagPresent(action.getParameter<std::string>("tag")))
                    SunBase::processAction(action);
            } else
                SunBase::processAction(action);
            if (action.getRecursive() == true && recursive == true)
                sendActionToAllSubNodes(action);
        }
    } else {
        if (action.parameterExists("tag") && ignoreTags == false) {
            if (tagPresent(action.getParameter<std::string>("tag")))
                SunBase::processAction(action);
        } else
            SunBase::processAction(action);
        if (action.getRecursive() == true && recursive == true)
            sendActionToAllSubNodes(action);
    }

}

} // sunglasses
