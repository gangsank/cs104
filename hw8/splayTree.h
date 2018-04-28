#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "rotateBST.h"

template <typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();
protected:
	void splay(Node<Key, Value> *r);
private:
	Node<Key,Value>* lastVisited(Node<Key,Value>* node, const Key& key);
	Node<Key,Value>* getBiggestNode(Node<Key,Value>*);
};

template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{

}

template<typename Key, typename Value>
Node<Key,Value>* SplayTree<Key,Value>::getBiggestNode(Node<Key,Value>* biggest)
{
	while (biggest->getRight()) 
	{
		biggest = biggest->getRight();
	}

	return biggest;
}

template <typename Key, typename Value>
Node<Key,Value>* SplayTree<Key, Value>::lastVisited(Node<Key,Value>* node, const Key& key)
{
	//reached the end
	if (!node)
	{
		return node->getParent();
	}

	else if (node->getKey() > key)
	{
		return lastVisited(node->getLeft(), key);
	}

	return lastVisited(node->getRight(), key);
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//if the key is already in the tree
	if(this->internalFind(keyValuePair.first))
	{
		splay(this->internalFind(keyValuePair.first));
		return;
	}

	else
	{
		BinarySearchTree<Key, Value>::insert(keyValuePair);
		splay(this->internalFind(keyValuePair.first));
	}
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	//Key does not exist in the tree
	if(find(key) == this->end())
	{
		splay(lastVisited(this->mRoot,key));
		return;
	}

	Node<Key,Value>* parent = this->internalFind(key)->getParent();

	//if parent is null
	if(!parent)
	{
		BinarySearchTree<Key,Value>::remove(key);
	}

	else
	{
		BinarySearchTree<Key,Value>::remove(key);
		splay(parent);
	}
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	Node<Key,Value>* exist = this->internalFind(key);

	//Key does not exist in the tree
	if(!exist)
	{
		splay(lastVisited(this->mRoot,key));
		return this->end();
	}

	splay(exist);
	return BinarySearchTree<Key,Value>::find(key);
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	//Find the smallest node
	Node<Key,Value>* smallest = this->getSmallestNode();
	return find(smallest->getKey());
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	//Find the biggest node
	Node<Key,Value>* biggest = getBiggestNode(this->mRoot);
	return find(biggest->getKey());
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	//Find the smallest node and delete it
	Node<Key,Value>* smallest = this->getSmallestNode();
	BinarySearchTree<Key,Value>::remove(smallest->getKey());
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{
	//Find the biggest node and delete it
	Node<Key,Value>* biggest = getBiggestNode(this->mRoot);
	BinarySearchTree<Key,Value>::remove(biggest->getKey());
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{
	while(r->getParent() != NULL)
	{
		//if grandparent of r, or parent of parent, is null
		if (r->getParent()->getParent() == NULL)
		{
			//rotate parent
			if(r==r->getParent()->getLeft())
			{
				this->rightRotate(r->getParent());
			}

			else if (r==r->getParent()->getRight())
			{
				this->leftRotate(r->getParent());
			}
		}

		//else if r and parent are both left children
		//zigzig
		else if(r == r->getParent()->getLeft() && 
			r->getParent() == r->getParent()->getParent()->getLeft())
		{
			//rotate grandparent, then rotate parent
			this->rightRotate(r->getParent()->getParent());
			this->rightRotate(r->getParent());
		}

		//else if r and parent are both right children
		//zigzig
		else if (r == r->getParent()->getRight() && 
			r->getParent() == r->getParent()->getParent()->getRight())
		{
			//rotate grandparent, then rotate parent
			this->leftRotate(r->getParent()->getParent());
			this->leftRotate(r->getParent());
		}

		//zigzag
		//rotate parent, then rotate grandparent
		else 
		{
			if (r == r->getParent()->getRight() &&
				r->getParent() == r->getParent()->getParent()->getLeft())
			{
				Node<Key, Value>* parent = r->getParent();
				Node<Key, Value>* grandparent = r->getParent()->getParent();
 				this->leftRotate(parent);
				this->rightRotate(grandparent);
			}

			else if (r == r->getParent()->getLeft() &&
				r->getParent() == r->getParent()->getParent()->getRight())
			{
				Node<Key, Value>* parent = r->getParent();
				Node<Key, Value>* grandparent = r->getParent()->getParent();
				this->rightRotate(parent);
				this->leftRotate(grandparent);
			}
		}
	}

	this->mRoot = r;
};
#endif