
// COS30008, Final Exam, 2022

#pragma once

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;
    using TTreeNode = TTree*;
    using TTreeStack = std::stack<const TTree*>;
    // had to use const_cast to remove the constness here
    // I think TTreeStack and fTTree shouldn't have the const-qualifiers to begin with
    const TTree* fTTree;                // ternary tree
    TTreeStack fStack;                  // traversal stack

public:

    using Iterator = TernaryTreePrefixIterator<T>;

    Iterator operator++(int)
    {
        Iterator old = *this;

        ++(*this);

        return old;
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter);
    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 4: TernaryTree Prefix Iterator

// This is similar to Iterator implementaion in PBS4, there are some differences I will point out.
private:

    // push subtree of aNode
    // dif 1: BTree iter push "left" node to stack first so #left->#Root->#right
    //  whilst TTree iter push right, mid, left, thus the order is #Root->#L->#M->#R
    void push_subtrees(const TTree* aNode)
    {
        // Push the subtrees from right to left onto the stack
        // must do an empty check for each individual subtrees
        if (!aNode->getRight().empty())
        {
            fStack.push(&aNode->getRight());
        }
        if (!aNode->getMiddle().empty())
        {
            fStack.push(&aNode->getMiddle());
        }
        if (!aNode->getLeft().empty())
        {
            fStack.push(&aNode->getLeft());
        }
    }

public:

    TernaryTreePrefixIterator(const TTree* aTTree) :fTTree(aTTree), fStack()
    {
        if (!(fTTree)->empty())
        {
            // "Initially, the stack contains only the root of the tree"
            fStack.push(fTTree);
        }
    }

    // iterator dereference
    const T& operator*() const
    {
        return **fStack.top();

    }

    // prefix increment
    // dif 2: BTree only need to push the right child after popped cause left has been visited
    // while TTree would have to push all of the children of the popped node
    Iterator& operator++()
    {
        // mismatch data type here, have to use const_cast for assignment to work
        TTreeNode lPopped = const_cast<TTreeNode>(fStack.top());
        // "always removes the top element from the stack"
        fStack.pop(); 
        // invoke the push_subtrees which push pushes the corresponding
        //subtrees from right to left unto the traversal stack
        push_subtrees(lPopped);
        return *this;
    }

    // iterator equivalence
    bool operator==(const Iterator& aOtherIter) const
    {
        // "tests the addresses of the trees and the respective stack sizes"
        return fTTree == aOtherIter.fTTree && fStack.size() == aOtherIter.fStack.size();
    }

    // auxiliaries
    // dif 3: BTree pushes the left-est node onto stack
    // whilst TTree pushes root
    Iterator begin() const
    {
        Iterator temp = *this;
        temp.fStack = TTreeStack();
        // once again, mismatch data type, have to use const_cast
        temp.fStack.push(const_cast<TTreeNode>(temp.fTTree));
        return temp;
    }

    Iterator end() const
    {
        Iterator temp = *this;
        temp.fStack = TTreeStack();
        return temp;
     
    }
};

