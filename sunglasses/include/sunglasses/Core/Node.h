// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef NODE_H
#define NODE_H

#include "Base.h"
#include "Service.h"

#include <iterator>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <memory>

namespace sunglasses {

template<typename T>
class Node;

/// Iterates through a network of nodes (depth first)
template<typename T>
class NodeIterator : std::iterator<std::bidirectional_iterator_tag,
								   Node<T>,
								   std::ptrdiff_t,
								   Node<T> *,
								   Node<T> &> {
public:
	/// Constructs the iterator from a pointer
	NodeIterator(Node<T> *_node = nullptr) : node(_node) { }
	NodeIterator(const NodeIterator<T> &other) = default;
	
	NodeIterator<T> & operator=(const NodeIterator<T> &other) = default;
	NodeIterator<T> & operator=(Node<T> *_node) { node = _node; return *this; }
	
	/// Destroys the iterator
	~NodeIterator() { }
	
	NodeIterator<T> & operator++() { next(); return *this; }
	NodeIterator<T> & operator++(int) { NodeIterator<T> copy(*this); (*this)++; return copy; }
	NodeIterator<T> & operator--() { previous(); return *this; }
	NodeIterator<T> & operator--(int) { NodeIterator<T> copy(*this); (*this)--; return copy; }
	
	bool operator==(const NodeIterator<T> &other) const { return (node == other.node); }
	bool operator!=(const NodeIterator<T> &other) const { return (node != other.node); }
	
	Node<T> & operator*() { return *node; }
	const Node<T> & operator*() const { return *node; }
	Node<T> * operator->() { return node; }
private:			
	void next() {
		if (node->children.length() > 0) {
			node = node->children[0].get();
		} else {
			// Node is end of a branch, go up
			node = node->parent;
			
			// Keep going until a node is found with a child to the right
			//while (node 
		}
	}
	
	void previous() {
	
	}
	
	Node<T> *node;
};

/// An abstract base class for Node
class INode : public Base {
public:
	virtual void init() = 0;
	virtual void processAction(Action action, bool) = 0;
};

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
template<typename T>
class Node : public INode {
public:
	/// The iterator type
	typedef NodeIterator<T> iterator;
	friend iterator;
	
	/// The const_iterator type
	typedef NodeIterator<const T> const_iterator;
	friend const_iterator;
	
    /// Constructs the node with a parent
    Node(Node *_parent = nullptr, std::initializer_list<std::string> _tags = {}) :
    		parent(_parent), tags(_tags) {
    	if (parent != nullptr)
			parent->addChild(this);
    }
    
    /// Destroys the node by deleting all of its children
    virtual ~Node() {
    	for (Node *child : children)
    		delete child;
    }
    
    /// Returns the begin iterator
    iterator begin() { return iterator(this); }
    
    /// Returns the begin const_iterator
    const_iterator cbegin() { return const_iterator(this); }
    
    
    /// Returns the end iterator
    iterator end() { return iterator(parent); }
    
    /// Returns the end const_iterator
    const_iterator cend() { return const_iterator(parent); }

    /// Initializes the object.
    /**
     * This member function does nothing, but exists so that you can use a Node
     * without subclassing it. It is recommended to override this.
     */
    virtual void init() { }

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
    virtual void processAction(Action action) {
    	if (action.parameterExists("exclude")) {
        	if (action.getParameterPointer<Node>("exclude") != this) {
      	  		if (action.parameterExists("tag")) {
                	if (tagPresent(action.getParameter<std::string>("tag")))
                    	Base::processAction(action);
            	} else
                	Base::processAction(action);
            if (action.getRecursive() == true)
                sendActionToAllChildren(action);
        	}
    	} else {
        	if (action.parameterExists("tag")) {
        	    if (tagPresent(action.getParameter<std::string>("tag")))
        	        Base::processAction(action);
        	} else
        	    Base::processAction(action);
        	if (action.getRecursive() == true)
        	    sendActionToAllChildren(action);
    	}
    }

    /// Checks that a tag is present.
    /**
     * This member function searches the node's tag list and returns true if the
     * tag in the parameter exists, or false if it doesn't.
     */
    bool tagPresent(std::string t) {
    	return (std::find(tags.begin(), tags.end(), t) != tags.end()) ? true : false;
    }

    /// Sends an action to all subnodes.
    /**
     * This functions sends the action (in the parameters) to all of the node's
     * subnodes when it is called.
     */
    void sendActionToAllChildren(Action action) {
    	for (size_t i = 0; i < children.size(); ++i)
     	   children[i]->processAction(action, false);
    	if (action.getRecursive())
        	for (size_t i = 0; i < children.size(); ++i)
            	children[i]->sendActionToAllChildren(action);
	}

    /// Appends a Node pointer to the subnode vector.
    /**
     * This member function adds the Node pointer (in the parameters) to the end
     * of the vector of subnodes. This subnode will receive recursive actions from the
     * parent node.
     * @param _child The node to add as a sub node
     */
    void addChild(Node *_child) {
    	if (find(children.begin(), children.end(), _child) == children.end()) {
    		if (children.size() > 0) {
    			(*(--children.end()))->right = _child;
    			_child->left = (*(--children.end()));
    		}
    	    children.push_back(_child);
    	    _child->parent = this;
    	}
	}
	
	/// Removes a Node from the vector of children
	void removeChild(Node *_child) {
		typename std::vector<Node *>::iterator point =
			std::find(children.begin(), children.end(), _child);
		
		_child->parent = nullptr;
		_child->left = nullptr;
		_child->right = nullptr;
		
		typename std::vector<Node *>::iterator left = (point - 1);
		typename std::vector<Node *>::iterator right = (left + 2);
		
		if (left >= children.begin())
			(*left)->right = ((right >= children.end()) ? nullptr : *right);
		if (right < children.end())
			(*right)->left = ((left < children.begin())? nullptr : *left);
		
		children.erase(point);
			
	}
	
	/// Sets the parent of the node
	/**
	 * Set the parent of the node to nullptr to have a node with no parent
	 */
	void setParent(Node *_parent) {
		// Remove from old parent
		if (parent != nullptr)
			parent->removeChild(this);

		// Add to new parent
		if (_parent != nullptr)
			_parent->addChild(this);
	}

    /// Adds a tag (string) to the vector of tags.
    void addTag(std::string t) { tags.push_back(t); }
    
    const Node * getParent() { return parent; }
    const Node * getLeft() { return left; }
    const Node * getRight() { return right; }
    
    const std::vector<Node<T> *> & getChildren() { return children; }
protected:
    /// Processes the action with control of recursion.
    /**
     * This method is the same as the public processAction, except it gives you
     * control over recursion (overrides the Action property). This is used
     * when processing a recursive action.
     */
    virtual void processAction(Action action, bool recursive) {
    	if (action.parameterExists("exclude")) {
        	if (action.getParameterPointer<Node>("exclude") != this) {
            	if (action.parameterExists("tag")) {
                	if (tagPresent(action.getParameter<std::string>("tag")))
                    	Base::processAction(action);
            	} else
                	Base::processAction(action);
            	if (action.getRecursive() == true && recursive == true)
                	sendActionToAllChildren(action);
        	}
    	} else {
        	if (action.parameterExists("tag")) {
            	if (tagPresent(action.getParameter<std::string>("tag")))
                	Base::processAction(action);
        	} else
            	Base::processAction(action);
        	if (action.getRecursive() == true && recursive == true)
            	sendActionToAllChildren(action);
    	}
    }

    /// A vector containing pointers to the node's children
    std::vector<Node<T> *> children;

    /// A pointer to the node's parent
    Node<T> *parent;
    
    /// Pointers to the node's left and right siblings
    Node<T> *left, *right;

    /// A vector of tags
    /**
     * A vector of strings that are tags. When an action with a parameter named 'tag'
     * is received and the ignoreTags member (bool) is false (default), the action
     * is only performed if this vector contains the tag parameter. The action is
     * always passed to the subnodes if recursive.
     */
    std::vector<std::string> tags;
};

} // namespace

#endif
