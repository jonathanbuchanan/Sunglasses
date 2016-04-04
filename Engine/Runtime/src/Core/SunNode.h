// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNNODE_H
#define SUNNODE_H

#include "SunBase.h"
#include "SunService.h"
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

/// A node class derived from SunBase
/**
 * SunNode is a class derived from SunBase. A single node can have multiple
 * children and multiple parents. It overrides the processAction member function
 * of SunBase, so that it sends an action to its subnodes upon receiving a SunAction
 * which has the recursive boolean set to true. It also looks for a string parameter
 * called tag, and only processes the action the node has that tag. If the ignoreTags
 * boolean is set to true, a SunNode will process an action even if it doesn't have
 * a matching tag.
 */
class SunNode : public SunBase {
public:
    /// The default constructor
    /**
     * This constructor initializes the node with empty parents, empty children,
     * an empty list of tags, and ignore tags set to false.
     */
	SunNode();

    /// Constructor for the tag list member (string)
    /**
     * This constructor initializes the node with empty parents, empty children,
     * ignore tags set to false, and a single tag.
     */
	SunNode(std::string _tag);

    /// Constructor for the tag list member (vector)
    /**
     * This constructor initializes the node with empty parents, empty children,
     * ignore tags set to false, and a list of tags (strings).
     */
	SunNode(std::vector<std::string> _tags);

    /// Initializes the object.
    /**
     * This member function does nothing, but exists so that you can use a SunNode
     * without subclassing it. It is recommended to override this.
     */
    virtual void init();

    /// Processes a SunAction.
    /**
     * This member function overrides the definition in SunBase. If a parameter
     * name 'tag' is present, the node only processes the action if that tag
     * is present in itself.
     * If ignoreTags (boolean) is set to true, it will still process an action even
     * if the node doesn't contain a matching tag. It sends the action to all of its
     * subnodes if the recursive boolean of the action is set to true. The success
     * of the tag check doesn't change the recursive behavior of the action.
     */
	virtual void processAction(SunAction action);

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
    void sendActionToAllSubNodes(SunAction action);

    /// Appends a SunNode pointer to the subnode vector.
    /**
     * This member function adds the SunNode pointer (in the parameters) to the end
     * of the vector of subnodes. This subnode will receive recursive actions from the
     * parent node.
     */
    virtual void addSubNode(SunNode *_subNode);

    /// OLD
    void findNode(std::string _path, SunNode &_node);

    /// OLD
    void findNode(std::string _path, SunNode *&_node);

    /// OLD
    void findNodeWithName(std::string _name, SunNode &_node);

    /// OLD
    virtual void findPointerNodeWithName(std::string _name, SunNode *&_node);

    virtual void recursiveDeleteSubnode(const SunNode *node);

    /// Gets the vector of subnodes.
    std::vector<SunNode *> getSubNodes() { return subNodes; }
    /// Gets the size of the vector of subnodes (int).
    int getSubNodesSize() { return subNodes.size(); }
    /// Gets the subnode (SunNode pointer) at the specified index (int).
    SunNode * getSubNodeAtIndex(int i) { return subNodes[i]; }

    /// Gets the level member (int).
    int getLevel() { return level; }

	/// Adds a tag (string) to the vector of tags.
	void addTag(std::string t) { tags.push_back(t); }

    /// Sets the ignore tags member (bool).
	void setIgnoreTags(bool i) { ignoreTags = i; }

    /// Gets the vector of parents.
    std::vector<SunNode *> & getParents() { return parents; }
    /// Gets the size of the vector of parents (int).
    int getParentsSize() { return parents.size(); }
    /// Gets the parent (SunNode pointer) at the specified index (int).
    SunNode * getParentAtIndex(int i) { return parents[i]; }
private:
    /// Processes the action with control of recursion.
    /**
     * This method is the same as the public processAction, except it gives you
     * control over recursion (overrides the SunAction property). This is used
     * when processing a recursive action.
     */
    virtual void processAction(SunAction action, bool recursive);

    /// The number of parents ready (useful when performing a recursive action with multiple parents)
    int parentsReady;

    /// A vector containing pointers to the node's subnodes
    std::vector<SunNode *> subNodes;

    /// A vector containing pointers to the node's parents
    std::vector<SunNode *> parents;

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

#endif
