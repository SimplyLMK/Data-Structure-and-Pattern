

#pragma once

#include "BinaryTreeSearch.h"

#include <stack>
#include <queue>


template<typename T>
class BinarySearchTreeIterator
{
private:

    // I decided to implement BFS as well because I am super exicted about this topic
    // I even have a git repo about using BFS and DFS to solve eight puzzle
    //  https://github.com/SimplyLMK/BFS-and-DFS-in-eight-puzzle.git
    // BFS and DFS works exactly the same logic, queue strucure makes all the difference.
    // you can see in my BFS implementation I just changed the code to use a queue struct 
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;
    // the structure of BFS is a queue if you think about it..
    using BTNQueue = std::queue<BTreeNode>;

    const BSTree& fBSTree;
    BTNStack fStack;
    BTNQueue fQueue;

    // say we have a tree structure with R as Root, its children is A and D
    // children of A is B and C. A is left-est node.
    

    // >| B | // R is init as root, and pushLeft(R) to the stack
    //  | A | // A is R's left-est node so pushLeft into stack
    //  | R | // B is A's left-est node, pushLeft B which is a leaf node
    
    //  |   | // operator* to print out B
    // >| A | // operator++ move iterator to (A), pop B and pushLeft nothing since B is leaf
    //  | R | // oper* to print A


    //  |   | // oper++ move iter to (C), pop A and pushLeft(C) leaf on stack
    // >| C | // * print out C
    //  | R | // ++ move iter to (R) pop C, pushleft nothing onto Stack

    //  |   |// * print R
    //  |   |// ++ pop C, pushLeft the right node D onto the Stack
    // >| R |

    //  |   | // when Stack is finally empty
    //  |   | // operator== return true when compare with Iterator end()
    //  |   | // inicate complete -> output:  B, A, C, R




    // push the node into the stack, ready to be pop
    // in this implemntation, we are going from left to right
    // but the right to left is valid as well
    void pushLeft(BTreeNode aNode)
    {
        if (!aNode->empty())
        {
            fStack.push(aNode);
            pushLeft(aNode->left);
        }
    }

public:

    using Iterator = BinarySearchTreeIterator<T>;

    BinarySearchTreeIterator(const BSTree& aBSTree) :fBSTree(aBSTree), fStack()//, fQueue()
    {
        pushLeft(aBSTree.fRoot);
    }

    // Dereference operator
    const T& operator*() const
    {
        // return key of the top node in the stack
        return fStack.top()->key;
        
    }

    //Moves the iterator to the next node in the tree
    Iterator& operator++()
    {

        BTreeNode lPopped = fStack.top();
        fStack.pop(); // pops the node at the top
        pushLeft(lPopped->right); //push that node into right subtree to the stack
        return *this;
    }
    Iterator operator++(int) // return copy of ite before incremented
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    // if equal -> iterating in the same tree && pointing to same node.
    bool operator==(const Iterator& aOtherIter) const { return &fBSTree == &aOtherIter.fBSTree && fStack == aOtherIter.fStack; }

    // opposite of ==
    bool operator!=(const Iterator& aOtherIter) const { return !(*this == aOtherIter); }

    Iterator begin() const
    {
        // Returns an iterator pointing to the leftmost node of the tree.

        Iterator temp = *this;
        temp.fStack = BTNStack();
        temp.pushLeft(temp.fBSTree.fRoot);
        return temp;
    }
    Iterator end() const
    {
        // Returns an iterator pointing to the NIL node.
        Iterator temp = *this;
        temp.fStack = BTNStack();
        return temp;
    }

    // BFS implementation, how it works is completely the same logic
    
    /*
    void enqueueLeft(BTreeNode aNode)
    {
        if (!aNode->empty())
        {
            fQueue.push(aNode);
            enqueueLeft(aNode->left);
            enqueueLeft(aNode->right);
        }
    }

    const T& operator*() const
   {
       return fQueue.front()->key;
   }
   Iterator& operator++()
   {
       fQueue.pop();
       return *this;
   }
   Iterator operator++(int)
   {
       Iterator temp = *this;
       ++(*this);
       return temp;
   }
   bool operator==(const Iterator& aOtherIter) const { return &fBSTree == &aOtherIter.fBSTree && fQueue == aOtherIter.fQueue; }

   bool operator!=(const Iterator& aOtherIter) const { return !(*this == aOtherIter); }

   Iterator begin() const
   {
       Iterator temp = *this;
       temp.fQueue = BTNQueue();
       temp.enqueueLeft(temp.fBSTree.fRoot);
       return temp;
   }
   Iterator end() const
   {
       Iterator temp = *this;
       temp.fQueue = BTNQueue();
       return temp;
   }
    */

};