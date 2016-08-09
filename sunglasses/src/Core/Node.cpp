// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/Node.h>

#include <iostream>

namespace sunglasses {

Node::Node() {
    parentsReady = 0;
    level = 0;
}

Node::Node(std::string _tag) : tags({_tag}) {
    Node();
}

Node::Node(std::vector<std::string> _tags) : tags(_tags) {
    Node();
}

void Node::init() {

}

void Node::processAction(Action action) {
    if (action.parameterExists("exclude")) {
        if (action.getParameterPointer<Node>("exclude") != this) {
            if (action.parameterExists("tag") && ignoreTags == false) {
                if (tagPresent(action.getParameter<std::string>("tag")))
                    Base::processAction(action);
            } else
                Base::processAction(action);
            if (action.getRecursive() == true)
                sendActionToAllSubNodes(action);
        }
    } else {
        if (action.parameterExists("tag") && ignoreTags == false) {
            if (tagPresent(action.getParameter<std::string>("tag")))
                Base::processAction(action);
        } else
            Base::processAction(action);
        if (action.getRecursive() == true)
            sendActionToAllSubNodes(action);
    }
}

bool Node::tagPresent(std::string t) {
    return (std::find(tags.begin(), tags.end(), t) != tags.end()) ? true : false;
}

void Node::sendActionToAllSubNodes(Action action) {
    for (size_t i = 0; i < subNodes.size(); ++i)
        subNodes[i]->processAction(action, false);
    if (action.getRecursive())
        for (size_t i = 0; i < subNodes.size(); ++i)
            subNodes[i]->sendActionToAllSubNodes(action);
}

void Node::addSubNode(Node *_subNode) {
    if (find(subNodes.begin(), subNodes.end(), std::shared_ptr<Node>(_subNode)) == subNodes.end()) {
        subNodes.push_back(std::shared_ptr<Node>(_subNode));
        _subNode->parents.push_back(this);
        _subNode->level = level + 1;
    }
}

void Node::addSubNode(const std::shared_ptr<Node> &_subNode) {
    if (find(subNodes.begin(), subNodes.end(), _subNode) == subNodes.end()) {
        subNodes.push_back(std::shared_ptr<Node>(_subNode));
        _subNode->parents.push_back(this);
        _subNode->level = level + 1;
    }
}

void Node::recursiveDeleteSubnode(Node *_node) {
    std::shared_ptr<Node> node = std::shared_ptr<Node>(_node);
    for (size_t i = 0; i < subNodes.size(); i++) {
        if (subNodes[i] == node)
            subNodes.erase(subNodes.begin() + i);
        else
            subNodes[i]->recursiveDeleteSubnode(_node);
    }
}

void Node::processAction(Action action, bool recursive) {
    if (action.parameterExists("exclude")) {
        if (action.getParameterPointer<Node>("exclude") != this) {
            if (action.parameterExists("tag") && ignoreTags == false) {
                if (tagPresent(action.getParameter<std::string>("tag")))
                    Base::processAction(action);
            } else
                Base::processAction(action);
            if (action.getRecursive() == true && recursive == true)
                sendActionToAllSubNodes(action);
        }
    } else {
        if (action.parameterExists("tag") && ignoreTags == false) {
            if (tagPresent(action.getParameter<std::string>("tag")))
                Base::processAction(action);
        } else
            Base::processAction(action);
        if (action.getRecursive() == true && recursive == true)
            sendActionToAllSubNodes(action);
    }

}

} // sunglasses
