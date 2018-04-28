#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
    public:
        bool sameKeys(const rotateBST& t2) const;
        void transform(rotateBST& t2) const;
        //These public variables are for cache analysis
        //int LeftRotateCount = 0;
        //int RightRotateCount = 0;
        
    protected:
        void leftRotate(Node<Key, Value>* r);
        void rightRotate(Node<Key, Value>* r);

    //Helper functions for my own
    private:
        void height_rearrange(Node<Key, Value>* node);
        Node<Key,Value>* sameKeysHelper(Node<Key, Value>* curr) const;
        void transformHelper(rotateBST& , Node<Key,Value>* , Node<Key,Value>* ,Node<Key,Value>* ,Node<Key,Value>* ) const;
        
};

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* current)
{
	//Nothing to rotate
    if(!current->getRight()) 
   	{
   		return;
    }

    Node<Key,Value>* target = current->getRight();
    Node<Key,Value>* left = current;

    if (target->getLeft())
    {
    	target->getLeft()->setParent(left);
        left->setRight(target->getLeft());

        if (!left->getParent())
        {
        	this->mRoot = target;
            target->setParent(NULL);
        }

        else
        {
        	target->setParent(left->getParent());

        	if (left->getParent()->getKey() < target->getKey())
        	{
        		left->getParent()->setRight(target);
        	}

        	else
        	{
        		left->getParent()->setLeft(target);
        	}
        }
  
        target->setLeft(left);
        left->setParent(target);
    }

    else
    {
    	if(!left->getParent())
    	{
    		this->mRoot = target;
            target->setParent(NULL);
    	}

    	else
    	{
    		target->setParent(left->getParent());

    		if (left->getParent()->getKey() < target->getKey())
    		{
    			left->getParent()->setRight(target);
    		}

    		else
    		{
    			left->getParent()->setLeft(target);
    		}
    	}

        target->setLeft(left);
        left->setParent(target);
        left->setRight(NULL);
    }
    //LeftRotateCount++;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* current)
{
    //Nothng to rotate
    if(!current->getLeft()) 
    {
    	return;
    }

    Node<Key,Value>* target = current->getLeft();
    Node<Key,Value>* right = current;

    if (target->getRight())
    {
    	target->getRight()->setParent(right);
        right->setLeft(target->getRight());

        if (!right->getParent())
        {
        	this->mRoot = target;
            target->setParent(NULL);
        }

        else
        {
        	target->setParent(right->getParent());

        	if (right->getParent()->getKey() < target->getKey())
        	{
        		right->getParent()->setRight(target);
        	}

        	else
        	{
        		right->getParent()->setLeft(target);
        	}
        }

        target->setRight(right);
        right->setParent(target);
    }

    else
    {
    	if (!right->getParent())
    	{
    		this->mRoot = target;
            target->setParent(NULL);
    	}

    	else
    	{
    		target->setParent(right->getParent());

    		if(right->getParent()->getKey() < target->getKey())
    		{
    			right->getParent()->setRight(target);
    		}

    		else
    		{
    			right->getParent()->setLeft(target);
    		}
    	}

        target->setRight(right);
        right->setParent(target);
        right->setLeft(NULL);
    }
    //RightRotateCount++;

}

template<typename Key, typename Value>
Node<Key,Value>* rotateBST<Key, Value>::sameKeysHelper(Node<Key, Value>* current) const
{
	if (!current->getRight())
	{
		Node<Key, Value>* parent = current->getParent();
		while(parent && current == parent->getRight())
		{
			current = parent;
			parent = parent->getParent();
		}
		current = parent;
	}

	else
	{
		current = current->getRight();
		while(current->getLeft())
		{
			current = current->getLeft();
		}
	}

	return current;
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
    Node<Key, Value>* first = this->getSmallestNode();
    Node<Key, Value>* second = t2.getSmallestNode();

    if(first->getKey() != second->getKey())
    {
        return false;
    }

    else
    {
        while(first && second)
        {
            if(first->getKey() != second->getKey())
            {
                return false;
            }
            
            first = sameKeysHelper(first);
            second = sameKeysHelper(second);
            
        }

        return true;
    }

    return false;
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::transformHelper(rotateBST& t2, Node<Key,Value>* t2left, Node<Key,Value>* t2right,
	Node<Key,Value>* thisLeft,Node<Key,Value>* thisRight)const
{
    if (!t2right)
    {
        //error check
    }

    else
    {
        while(thisRight->getKey() != t2right->getKey())
        {
            t2.leftRotate(t2right);
            t2right = t2right->getParent();
        }
        transformHelper(t2,t2right->getLeft(),t2right->getRight(),thisRight->getLeft(),thisRight->getRight());
    }

    if (!t2left)
    {
        //error check
    }

    else
    {
        while(thisLeft->getKey() != t2left->getKey())
        {
            t2.rightRotate(t2left);
            t2left = t2left->getParent();
        }

        transformHelper(t2,t2left->getLeft(),t2left->getRight(),thisLeft->getLeft(),thisLeft->getRight());
    }
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
    if(sameKeys(t2))
    {
        while(t2.mRoot->getLeft())
        {
            t2.rightRotate(t2.mRoot);
        }

        Node<Key,Value>* temp = t2.mRoot->getRight();

        while(temp)
        {
            while(temp->getLeft())
            {    
                t2.rightRotate(temp);
                temp = temp->getParent();
            }

            if(!temp->getLeft())
            {
                temp = temp->getRight();
            }

            if(!temp->getLeft())
            {
                temp = temp->getRight();
            }   
        }

        while(this->mRoot->getKey() != t2.mRoot->getKey())
        {    
            t2.leftRotate(t2.mRoot);
        }

        transformHelper(t2, t2.mRoot->getLeft(), t2.mRoot->getRight(),this->mRoot->getLeft(),this->mRoot->getRight());
    }
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::height_rearrange(Node<Key, Value>* node)
{
    while (node)
    {
        int lh = 0;
        int rh = 0;
        int h = 0;

        if(node->getLeft())
        {
            lh = node->getLeft()->getHeight();
        }

        if (node->getRight())
        {
            rh = node->getRight()->getHeight();
        }

        if(lh < rh) 
        {
            h = rh;
        }   
    
        else 
        {
            h = lh;
        }

        //Compute the height for the node
        node->setHeight(h+1);
        node = node->getParent();
    }
}
#endif
