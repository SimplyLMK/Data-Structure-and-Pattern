#pragma once 

#include "BinaryTreeNode.h" 

#include <stdexcept> 

// Problem 3 requirement 
template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree
{
private:

    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;

    BTreeNode fRoot;

public:

    BinarySearchTree() :fRoot(&BNode::NIL) {}

    ~BinarySearchTree() 
    { 
        if (!fRoot->empty()) delete fRoot;
    }

    bool empty() const 
    { 
        return fRoot->empty(); 
    }

    size_t height() const
    {
        // invoke the #height# method in Node class
        return empty() ? throw domain_error("No height") : fRoot->height();
    }

    bool insert(const T& aKey)
    {
        // same as the method in Node but we dont need to compare which side to insert
        // invoke the #insert# method we created on Node class on the root node.
        return empty() ? (fRoot = new BNode(aKey), true) : fRoot->insert(aKey);
    }
    bool remove(const T& aKey)
    {
        // case empty && root is leaf node
        return empty() ? throw domain_error("Cannot move empty tree") : fRoot->leaf() ? 

        // compare the key, if true -> invoke #remove# onto fRoot
        (fRoot->key != aKey ? false : (fRoot = &BNode::NIL, true)) : fRoot->remove(aKey, &BNode::NIL);
    }



    using Iterator = BinarySearchTreeIterator<T>;


    friend class BinarySearchTreeIterator<T>;

    Iterator begin() const { return Iterator(*this).begin(); }
    Iterator end() const { return Iterator(*this).end(); }
};

