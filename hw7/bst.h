#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the clear() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	private:
	//Helper functions for my own
	Node<Key,Value>* FindHelper(Node<Key,Value>* node, const Key& key) const;
	void insertHelper(Node<Key,Value>* node, const std::pair<const Key,Value>& keyValuePair);
	void clearHelper(Node<Key,Value>* node);
	int balanceHelper(Node<Key,Value>* node);
	int comparison(int first, int second);
	int height_arrange(Node<Key, Value>* node);
	Node<Key, Value>* removeHelper(Node<Key, Value>* current, const Key& key);
	Node<Key,Value>* findPred(Node<Key, Value>* current);
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	if (mRoot == NULL)
	{
		return 0;
	}

	return mRoot->getHeight();
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::balanceHelper(Node<Key,Value>* node)
{
	if (node == NULL)
	{
		return 0;
	}

	int lh = balanceHelper(node->getLeft());

	if(lh == -1)
	{
		return -1;
	}

	int rh = balanceHelper(node->getRight());

	if (rh == -1)
	{
		return -1;
	}

	int balance = lh - rh;

	if (abs(balance) > 1)
	{
		return -1;
	}

	else
	{
		if (lh > rh)
		{
			return lh+1;
		}

		else if (lh == rh)
		{
			return lh+1;
		}

		else
		{
			return rh+1;
		}
	}
}

/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	
	if (balanceHelper(mRoot) == -1)
	{
		return false;
	}

	else
	{
		return true;
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insertHelper(Node<Key,Value>* node, const std::pair<const Key,Value>& keyValuePair)
{
	//If the key already exists, quit.
	if (find(keyValuePair.first) != end())
	{
		return;
	}

	//Found the location
	if (node == NULL)
	{
		node = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);
		node->setHeight(1);
		node->setLeft(NULL);
		node->setRight(NULL);

		node->setHeight(height_arrange(mRoot));

		return;
	}

	//Recursion
	//if the new key is smaller, go left
	if (node->getKey() > keyValuePair.first)
	{
		if (node->getLeft() == NULL)
		{
			Node<Key, Value>* temp = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, node);
			node->setLeft(temp);
			temp->setLeft(NULL);
			temp->setRight(NULL);
			temp->setHeight(1);

			temp->setHeight(height_arrange(mRoot));

			return;
		}

		else
		{
			insertHelper(node->getLeft(), keyValuePair);
		}
	}

	//if the new key is bigger, go right
	else
	{
		if (node->getRight() == NULL)
		{
			Node<Key, Value>* temp = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, node);
			node->setRight(temp);
			temp->setRight(NULL);
			temp->setLeft(NULL);
			temp->setHeight(1);

			temp->setHeight(height_arrange(mRoot));

			return;
		}

		else
		{
			insertHelper(node->getRight(), keyValuePair);
		}
	}

}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//Checking if the root is empty
	if (mRoot == NULL)
	{
		mRoot = new Node<Key,Value> (keyValuePair.first, keyValuePair.second, NULL);
		mRoot->setHeight(1);
		mRoot->setLeft(NULL);
		mRoot->setRight(NULL);
		return;
	}

	//Recursive call on insertion
	insertHelper(mRoot, keyValuePair);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findPred(Node<Key, Value>* current){

    Node<Key, Value>* temp = current->getLeft();
    while (temp->getRight() != NULL)
    {
        temp = temp->getRight();
    }
	return temp;
    
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::removeHelper(Node<Key, Value>* current, const Key& key)
{
	if(current == NULL) 
	{
		return current;
	}

	if(current->getKey() < key)
	{
		current->setRight(removeHelper(current->getRight(), key));
		current->setHeight(height_arrange(current));
	}

	else if(current->getKey() > key)
	{
		current->setLeft(removeHelper(current->getLeft(), key));
		current->setHeight(height_arrange(current));
	}

	else
	{	
		if(current->getLeft() == NULL && current->getRight() == NULL){
			delete current;
			current = NULL;
		}

		else if(current->getLeft() == NULL)
		{
			Node<Key, Value>* temp = current;
			current = current->getRight();
			current->setParent(temp->getParent());
			delete temp;
			current->setHeight(height_arrange(current));
		}

		else if(current->getRight() == NULL)
		{
			Node<Key, Value>* temp = current;
			current = current->getLeft();
			current->setParent(temp->getParent());
			delete temp;
			current->setHeight(height_arrange(current));
		}

		else
		{
			//target is found and it has two children.
			Node<Key, Value>* temp = findPred(current);
			if(temp->getParent()->getKey() == current->getKey())
			{
				temp->setRight(current->getRight());
				temp->setParent(current->getParent());
				current->getRight()->setParent(temp);
			}

			else if(temp->getLeft() == NULL)
			{
				temp->getParent()->setRight(NULL);
				temp->setLeft(current->getLeft());
				temp->setRight(current->getRight());
				temp->setParent(current->getParent());
				current->getRight()->setParent(temp);
				current->getLeft()->setParent(temp);
			}

			else
			{
				temp->getParent()->setRight(temp->getLeft());
				temp->getLeft()->setParent(temp->getParent());
				temp->setLeft(current->getLeft());
				temp->setRight(current->getRight());
				temp->setParent(current->getParent());
				current->getRight()->setParent(temp);
				current->getLeft()->setParent(temp);
			}
			
			if(current->getParent() != NULL)
			{
				if(current->getParent()->getKey() > temp->getKey())
				{
					current->getParent()->setLeft(temp);
				}
				else
				{
					current->getParent()->setRight(temp);
				}
			}

				delete current;
				temp->setHeight(height_arrange(temp));
				return temp;	
		}
		
		return current;
	}
	return current;
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	mRoot = removeHelper(mRoot, key);
}

template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::clearHelper(Node<Key,Value>* node)
{
	if (node == NULL)
	{
		return;
	}

	clearHelper(node->getLeft());
	clearHelper(node->getRight());

	delete node;
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{	
	clearHelper(mRoot);
	mRoot = NULL;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	if (mRoot->getLeft() == NULL)
	{
		return mRoot;
	}

	Node<Key, Value>* smallest = mRoot;

	while (smallest->getLeft() != NULL) 
	{
		smallest = smallest->getLeft();
	}

	return smallest;
}

template<typename Key, typename Value>
Node<Key,Value>* BinarySearchTree<Key, Value>::FindHelper(Node<Key,Value>* node, const Key& key) const
{
	if (node == NULL || node->getKey() == key)
	{
		return node;
	}

	else if (node->getKey() < key)
	{
		return FindHelper(node->getRight(), key);
	}

	return FindHelper(node->getLeft(), key);
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	// TODO
	Node<Key, Value>* target = FindHelper(mRoot, key);

	return target;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::comparison(int first, int second)
{
	if(first < second) 
	{
		return second;
	}	
	
	else 
	{
		return first;
	}
}

//This function rearrange all the height of nodes.
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height_arrange(Node<Key, Value>* curr)
{
	int lh=0;
	int rh=0;

	if (curr->getLeft() == NULL)
	{
		lh = 1;
	}

	else 
	{
		lh= height_arrange(curr->getLeft())+1;
	}

	if (curr->getRight() == NULL)
	{
		rh = 1;
	}

	else
	{
		rh = height_arrange(curr->getRight())+1;
	}

	curr->setHeight(comparison(lh, rh));

	return comparison(lh, rh);

}
/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/
#endif