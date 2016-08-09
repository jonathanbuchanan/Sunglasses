// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef NODE_H
#define NODE_H

#include "Base.h"
#include "Service.h"

#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <memory>

namespace sunglasses {

/// A node class derived from Base
/**
 * Node is a class derived from Base. A single node can have multiple
 * children and multiple parents. It overrides the processAction member function
 * of Base, so that it sends an action to its subnodes upon receiving a Action
 * which has the recursive boolean set to true. It also looks for a string parameter
 * called tag, and only processes the action the node has that tag. If the ignoreTags
 * boolean is set to true, a Node will process an action even if it doesn't have
 * a matching tag.
 */
class Node : public Base {
public:
    /// The default constructor
    /**
     * This constructor initializes the node with empty parents, empty children,
     * an empty list of tags, and ignore tags set to false.
     */
    Node();

    /// Constructor for the tag list member (string)
    /**
     * This constructor initializes the node with empty parents, empty children,
     * ignore tags set to false, and a single tag.
     */
    Node(std::string _tag);

    /// Constructor for the tag list member (vector)
    /**
     * This constructor initializes the node with empty parents, empty children,
     * ignore tags set to false, and a list of tags (strings).
     */
    Node(std::vector<std::string> _tags);

    /// Initializes the object.
    /**
     * This member function does nothing, but exists so that you can use a Node
     * without subclassing it. It is recommended to override this.
     */
    virtual void init();

    /// Processes a Action.
    /**
     * This member function overrides the definition in Base. If a parameter
     * name 'tag' is present, the node only processes the action if that tag
     * is present in itself.
     * If ignoreTags (boolean) is set to true, it will still process an action even
     * if the node doesn't contain a matching tag. It sends the action to all of its
     * subnodes if the recursive boolean of the action is set to true. The success
     * of the tag check doesn't change the recursive behavior of the action.
     */
    virtual void processAction(Action action);

    /// Checks that a tag is present.
    /**
     * This member function searches the node's tag list and returns true if the
     * tag in the parameter exists, or false if it doesn't.
     */
    bool tagPresent(std::string t);

    /// Sends an action to all subnodes.
    /**
     * This functions sends the action (in the parameters) to all of the node's
     * subnodes when it is called.
     */
    void sendActionToAllSubNodes(Action action);

    /// Appends a Node pointer to the subnode vector.
    /**
     * This member function adds the Node pointer (in the parameters) to the end
     * of the vector of subnodes. This subnode will receive recursive actions from the
     * parent node.
     * @param _subNode The node to add as a sub node
     */
    virtual void addSubNode(Node *_subNode);

    /// Appends a Node pointer to the subnode vector.
    /**
     * This member function adds the Node pointer (in the parameters) to the end
     * of the vector of subnodes. This subnode will receive recursive actions from the
     * parent node.
     * @param _subNode The node to add as a sub node
     */
    virtual void addSubNode(const std::shared_ptr<Node> &_subNode);

    /// Deletes a node from the list of children and makes every other child do this.
    /**
     * This member function is designed to remove a node from a tree. The node that
     * receives this will search its subnodes for the node and delete any that match,
     * then it will call this function on all other sub nodes.
     * @param _node The node to be deleted
     */
    virtual void recursiveDeleteSubnode(Node *_node);

    /// Gets the size of the vector of subnodes (int).
    int getSubNodesSize() { return subNodes.size(); }

    /// Gets the level member (int).
    int getLevel() { return level; }

    /// Adds a tag (string) to the vector of tags.
    void addTag(std::string t) { tags.push_back(t); }

    /// Sets the ignore tags member (bool).
    void setIgnoreTags(bool i) { ignoreTags = i; }

    /// Gets the size of the vector of parents (int).
    int getParentsSize() { return parents.size(); }

    /// Gets the parent (Node pointer) at the specified index (int).
    Node * getParentAtIndex(int i) { return parents[i]; }
protected:
    /// Processes the action with control of recursion.
    /**
     * This method is the same as the public processAction, except it gives you
     * control over recursion (overrides the Action property). This is used
     * when processing a recursive action.
     */
    virtual void processAction(Action action, bool recursive);

    /// The number of parents ready (useful when performing a recursive action with multiple parents)
    int parentsReady;

    /// A vector containing pointers to the node's subnodes
    std::vector<std::shared_ptr<Node>> subNodes;

    /// A vector containing pointers to the node's parents
    std::vector<Node *> parents;

    /// The number of 'levels' it is from the root node
    int level;

    /// A vector of tags
    /**
     * A vector of strings that are tags. When an action with a parameter named 'tag'
     * is received and the ignoreTags member (bool) is false (default), the action
     * is only performed if this vector contains the tag parameter. The action is
     * always passed to the subnodes if recursive.
     */
    std::vector<std::string> tags;

    /// A boolean controlling whether the node ignores tags
    /**
     * Actions with a parameter named 'tag' will still be performed even if the tags
     * vector doesn't contain the specified tag.
     */
    bool ignoreTags = false;
};

} // namespace

#endif
