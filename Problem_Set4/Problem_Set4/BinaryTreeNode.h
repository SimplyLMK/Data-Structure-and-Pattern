// COS30008, Problem Set 4, Problem 1, 2022
#pragma once
#include <stdexcept>
#include <algorithm>
#include<iostream>
template<typename T>
struct BinaryTreeNode
{
	using BNode = BinaryTreeNode<T>;
	using BTreeNode = BNode*;
	T key;
	BTreeNode left;
	BTreeNode right;
	static BNode NIL;
	const T& findMax() const
	{
		if (empty())
		{
			throw std::domain_error("Empty tree encountered.");
		}
		return right->empty() ? key : right->findMax();
	}
	const T& findMin() const
	{
		if (empty())
		{
			throw std::domain_error("Empty tree encountered.");
		}
		return left->empty() ? key : left->findMin();
	}
	bool remove(const T& aKey, BTreeNode aParent)
	{
		BTreeNode x = this;
		BTreeNode y = aParent;
		while (!x->empty())
		{
			if (aKey == x->key)
			{
				break;
			}
			y = x; // new parent
			x = aKey < x->key ? x->left : x->right;
		}
		if (x->empty())
		{
			return false; // delete failed
		}
		if (!x->left->empty())
		{
			const T& lKey = x->left->findMax(); // find max to left
			x->key = lKey;
			x->left->remove(lKey, x);
		}
		else
		{
			if (!x->right->empty())
			{
				const T& lKey = x->right->findMin(); // find min to right
				x->key = lKey;
				x->right->remove(lKey, x);
			}
			else
			{
				if (y != &NIL) // y can be NIL
				{
					if (y->left == x)
					{
						y->left = &NIL;
					}
					else
					{
						y->right = &NIL;
					}
				}
				delete x; // free deleted node
			}
		}
		return true;
	}
	// PS4 starts here
	BinaryTreeNode() : key(T()), right(&NIL), left(&NIL) {};
	// copy constructor
	BinaryTreeNode(const T& aKey) :key(aKey), left(&NIL), right(&NIL) { std::cout << "copied"<<std::endl; }
	
	// move constructor
	BinaryTreeNode(T&& aKey) :key(std::move(aKey)), left(&NIL), right(&NIL) { std::cout << "moved" << std::endl; }
	
	//destructor
	~BinaryTreeNode()
	{
		if (!left->empty()) delete left;
		if (!right->empty()) delete right;
	}

	bool empty() const
	{ 
		return this == &NIL; 
	}
	
	bool leaf() const
	{
		return left->empty() && right->empty();
		
	}

	size_t height() const
	{
		if (empty()) throw std::domain_error("Empty Tree encountered");

		// Tree height == maximum of the heights of its (left and right subtrees) + 1.
		return std::max(left != &NIL ? left->height() + 1 : 0, right != &NIL ? right->height() + 1 : 0);
	}
	
	bool insert(const T& aKey)
	{
		if (empty()) return false;

		// check duplication
		if (aKey == key) return false;

		//compare, inserts the key into the left subtree if less than the current key && vice versa
		BinaryTreeNode*& node = aKey < key ? left : right;
		// if nothing to compare, create new node with that key
		if (node->empty()) node = new BNode(aKey);
		else return node->insert(aKey);

		return true;
	}


};
template<typename T>
BinaryTreeNode<T> BinaryTreeNode<T>::NIL;
