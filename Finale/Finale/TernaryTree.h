
// COS30008, Final Exam, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
class TernaryTreePrefixIterator;

template<typename T>
class TernaryTree
{
public:

    using TTree = TernaryTree<T>;
    using TSubTree = TTree*;

private:

    T fKey;
    TSubTree fSubTrees[3];

    // private default constructor used for declaration of NIL
    TernaryTree() :
        fKey(T())
    {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
    }

public:

    using Iterator = TernaryTreePrefixIterator<T>;

    static TTree NIL;           // sentinel

    // getters for subtrees
    const TTree& getLeft() const { return *fSubTrees[0]; }
    const TTree& getMiddle() const { return *fSubTrees[1]; }
    const TTree& getRight() const { return *fSubTrees[2]; }

    // add a subtree
    void addLeft(const TTree& aTTree) { addSubTree(0, aTTree); }
    void addMiddle(const TTree& aTTree) { addSubTree(1, aTTree); }
    void addRight(const TTree& aTTree) { addSubTree(2, aTTree); }

    // remove a subtree, may through a domain error
    const TTree& removeLeft() { return removeSubTree(0); }
    const TTree& removeMiddle() { return removeSubTree(1); }
    const TTree& removeRight() { return removeSubTree(2); }

    /////////////////////////////////////////////////////////////////////////
    // Problem 1: TernaryTree Basic Infrastructure

// Disclaimer: I will be referencing alot of Dr.Markus lecture slides for this final
    // His framework works on N-Ary tree, meaning it works for 3-Ary Tree
    // " " on comments are quotation of the guide's intructions


    // remove a subtree, may throw a domain error [22]
    // reference: Lecture 11 slide 398
    const TTree& removeSubTree(size_t aSubtreeIndex)
    {
        // "guarantee that empty trees are not removed"
        if ((aSubtreeIndex < 3) && !fSubTrees[aSubtreeIndex]->empty())
        {
            const TTree& removedSubTree = *fSubTrees[aSubtreeIndex];
            //the removed "pointer must be set the address of NIL"
            fSubTrees[aSubtreeIndex] = &NIL;
            return removedSubTree; // "return constant reference"
        }
        else
        {
            // else throw domain error
            throw std::domain_error("Subtree is NIL");
        }

    }

    
    // add a subtree; must avoid memory leaks; may throw domain error [18]
    // reference: Lecture 11 slide 400
    void addSubTree(size_t aSubtreeIndex, const TTree& aTTree)
    {
        
        if (!empty())
        {
            //  "index must be valid " -> 3-ary tree so can not > 3  
            if (aSubtreeIndex < 3)
            {
                // "the slot in the array fSubTrees must be available"
                if (fSubTrees[aSubtreeIndex]->empty())
                {
                    // "adds a new 3 - ary subtree at index aSubtreeIndex"
                    fSubTrees[aSubtreeIndex] = const_cast<TTree*>(&aTTree);
                }
                else
                {
                    throw std::domain_error("Subtree is not NIL");
                }
            }
            else
            {
                throw std::out_of_range("Illegal index");
            }
        }
        else
        {
            throw std::domain_error("Empty NTREE");
        }
    }

public:

    // TernaryTree l-value constructor [10]
    TernaryTree(const T& aKey) : fKey(aKey)
    {
        // setting up, so the inital tree branches are NIL
        for (int i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
            
    }

    // destructor (free sub-trees, must not free empty trees) [14]
    // reference: Lecture 11 slide 395
    ~TernaryTree()
    {
        // "empty tree must not be deleted.It is unique and system - created"
        if (empty())
        {
            std::cout << "Delete NIL" << std::endl;
        }

        // iterate over 3 subtrees and delete every one of them
        for (int i = 0; i < 3; i++)
        {
            if (!fSubTrees[i]->empty())
            {
                // uncomment the line below to see the correct node deletion
                //std::cout << "Delete node:" << fSubTrees[i]->fKey << std::endl;
                delete fSubTrees[i];
            }

        }

    }

    // return key value, may throw domain_error if empty [2]
    const T& operator*() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree!!!");
        }
        return fKey;
    }

    // returns true if this ternary tree is empty [4]
    bool empty() const
    {
        return this == &NIL;
    }

    // returns true if this ternary tree is a leaf [10]
    bool leaf() const
    {
        // iterate over 3 subtrees
        for (int i = 0; i < 3; i++)
        {
            // if that branch has children
            if (!fSubTrees[i]->empty())
            {
                return false;
            }
        }         
        return true;
    }

    // return height of ternary tree, may throw domain_error if empty [48]
    size_t height() const
    {
        // "height of an empty tree is undefined"
        if (empty())
        {
            throw domain_error("Operation not supported");
        }

        // leaf has no children so its carried 0 weight to the calc
        if (leaf())
        {
            return 0;
        }

        // calculate the height of each subtree
        size_t Left_H = fSubTrees[0]->height();
        size_t Mid_H = fSubTrees[1]->height();
        size_t Right_H = fSubTrees[2]->height();

        // return the maximum height + 1
        return max({ Left_H, Mid_H, Right_H }) + 1;

    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 2: TernaryTree Copy Semantics

      // Working with l-value referece (T&) :

    // copy constructor, must not copy empty ternary tree
    TernaryTree(const TTree& aOtherTTree)
    {
        if (!aOtherTTree.empty())
        {
            // create a copy of an object when its instantialise
            for (size_t i = 0; i < 3; i++) fSubTrees[i] = &NIL;
            *this = aOtherTTree;
        }
        else
        {
            // "copy control must not create copies of empty trees"
            throw std::domain_error("Can not create copies of empty tree");
        }
        
    }

    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL
    TTree& operator=(const TTree& aOtherTTree)
    {
        // reference: Lecture 11 slide 401
        if (this != &aOtherTTree) //prevent self assignment
            if (!aOtherTTree.empty())
            {
                // clean up
                this->~TernaryTree();

                //copy payload
                fKey = aOtherTTree.fKey;

                // copying (this) from existing tree(aOtherTree)
                for (size_t i = 0; i < 3; i++)
                    if (!aOtherTTree.fSubTrees[i]->empty())
                    {
                        fSubTrees[i] = aOtherTTree.fSubTrees[i]->clone();
                    }
                    else
                    {
                        fSubTrees[i] = &NIL;
                    }
            }
            else throw std::domain_error("Copying of NIL detected");
        return *this;
    }

    // clone ternary tree, must not copy empty trees
    TSubTree clone() const
    {
        // reference: Lecture 11 slide 403
        if (!empty())
        {
            return new TTree(*this);
        }
        else
        {
            throw domain_error("Clonning of NIL detected");
        }
    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 3: TernaryTree Move Semantics
    
    // Working with r-value references (T&&)
    
    //The whole implementation is similar to Problem 2 so I wont comment
    // We just use std::move based on Problem 2 logical implementation

    // TTree r-value constructor
    TernaryTree(T&& aKey) :fKey(std::move(aKey))
    {
        for (int i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
    }

    // move constructor, must not copy empty ternary tree
    TernaryTree(TTree&& aOtherTTree)
    {
        for (size_t i = 0; i < 3; i++)
            fSubTrees[i] = &NIL;

        *this = move(aOtherTTree);
    }

    // move assignment operator, must not copy empty ternary tree
    TTree& operator=(TTree&& aOtherTTree)
    {
        if (this != &aOtherTTree)
            if (!aOtherTTree.empty())
            {
                this->~TernaryTree();

                fKey = std::move(aOtherTTree.fKey);

                for (int i = 0; i < 3; i++)
                    if (!aOtherTTree.fSubTrees[i]->empty())
                    {
                        fSubTrees[i] = const_cast<TSubTree>(&aOtherTTree.removeSubTree(i));
                    }
                    else
                    {
                        fSubTrees[i] = &NIL;
                    }
            }
            else
            {
                throw domain_error("Moving of NIL detected");
            }
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

    // return ternary tree prefix iterator positioned at start
    Iterator begin() const
    {
        return Iterator(this).begin();
    }

    // return ternary prefix iterator positioned at end
    Iterator end() const
    {
        return Iterator(this).end();
    }

};

template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;


