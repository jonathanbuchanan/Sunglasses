#ifndef TREE_H
#define TREE_H

namespace sunglasses {

/// A node in the tree
/**
 * A node inside the tree that has pointers to
 * its parent, right node, left node, first child, and left child.
 */
template<typename T>
class TreeNode {
public:
    /// Creates the node with a pointer to the parent (optional)
    TreeNode(TreeNode<T> *_parent = nullptr) : parent(_parent) {}
    
    /// A pointer to the node's parent
    TreeNode<T> *parent;
    
    /// A pointer to the node's left and right siblings
    TreeNode<T> *left, right;
    
    /// A pointer to the node's first and last children
    TreeNode<T> *firstChild, *lastChild;
private:

};

/// A tree made of nodes
template<typename T>
class Tree {
public:

protected:
    /// The root node of the tree
    TreeNode<T> root;
private:

};

}

#endif
