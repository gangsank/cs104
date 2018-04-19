#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"
#include <set>

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
    public:
        bool sameKeys(const rotateBST& t2) const;
        void transform(rotateBST& t2) const;
        
    protected:
        void leftRotate(Node<Key, Value>* r);
        void rightRotate(Node<Key, Value>* r);

    //Helper functions for my own
    private:
        int height_arrange(Node<Key, Value>* curr);
        int comparison(int first, int second);
        Node<Key,Value>* sameKeysHelper(Node<Key, Value>* curr) const;
        void transformHelper1(rotateBST& ) const;
        Node<Key,Value>* transformHelper2(rotateBST& , Node<Key,Value>* curr)const;
        void transformHelper3(rotateBST& , Node<Key,Value>* , Node<Key,Value>* ,Node<Key,Value>* ,Node<Key,Value>* ) const;
};

template<typename Key, typename Value>
int rotateBST<Key, Value>::comparison(int first, int second)
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

template<typename Key, typename Value>
int rotateBST<Key, Value>::height_arrange(Node<Key, Value>* curr)
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

//Constant
template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* current){

	//Nothing to rotate
    if(current->getRight() == NULL) 
   	{
   		return;
    }

    Node<Key,Value>* top = current->getRight();
    Node<Key,Value>* left = current;

    if (top->getLeft() != NULL)
    {
    	top->getLeft()->setParent(left);
        left->setRight(top->getLeft());

        if (left->getParent() == NULL)
        {
        	this->mRoot = top;
            top->setParent(NULL);
        }

        else
        {
        	top->setParent(left->getParent());

        	if (left->getParent()->getKey() < top->getKey())
        	{
        		left->getParent()->setRight(top);
        	}

        	else
        	{
        		left->getParent()->setLeft(top);
        	}
        }
  
        top->setLeft(left);
        left->setParent(top);
    }

    else
    {
    	if(left->getParent() == NULL)
    	{
    		this->mRoot = top;
            top->setParent(NULL);
    	}

    	else
    	{
    		top->setParent(left->getParent());

    		if (left->getParent()->getKey() < top->getKey())
    		{
    			left->getParent()->setRight(top);
    		}

    		else
    		{
    			left->getParent()->setLeft(top);
    		}
    	}

        top->setLeft(left);
        left->setParent(top);
        left->setRight(NULL);
    }

	//Update heights
    this->mRoot->setHeight(height_arrange(this->mRoot));
}

//Constant
template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* current){
    
    //Nothng to rotate
    if(current->getLeft() == NULL) 
    {
    	return;
    }

    Node<Key,Value>* top = current->getLeft();
    Node<Key,Value>* right = current;

    if (top->getRight() != NULL)
    {
    	top->getRight()->setParent(right);
        right->setLeft(top->getRight());

        if (right->getParent() == NULL)
        {
        	this->mRoot = top;
            top->setParent(NULL);
        }

        else
        {
        	top->setParent(right->getParent());

        	if (right->getParent()->getKey() < top->getKey())
        	{
        		right->getParent()->setRight(top);
        	}

        	else
        	{
        		right->getParent()->setLeft(top);
        	}
        }

        top->setRight(right);
        right->setParent(top);
    }

    else
    {
    	if (right->getParent() == NULL)
    	{
    		this->mRoot = top;
            top->setParent(NULL);
    	}

    	else
    	{
    		top->setParent(right->getParent());

    		if(right->getParent()->getKey() < top->getKey())
    		{
    			right->getParent()->setRight(top);
    		}

    		else
    		{
    			right->getParent()->setLeft(top);
    		}
    	}

        top->setRight(right);
        right->setParent(top);
        right->setLeft(NULL);
    }

    //Update heights
    this->mRoot->setHeight(height_arrange(this->mRoot));
}

template<typename Key, typename Value>
Node<Key,Value>* rotateBST<Key, Value>::sameKeysHelper(Node<Key, Value>* curr) const
{
	if (curr->getRight() == NULL)
	{
		Node<Key, Value>* parent = curr->getParent();
		while(parent != NULL && curr == parent->getRight())
		{
			curr = parent;
			parent = parent->getParent();
		}
		curr = parent;
	}

	else
	{
		curr = curr->getRight();
		while(curr->getLeft() != NULL)
		{
			curr = curr->getLeft();
		}
	}

	return curr;
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
    Node<Key, Value>* first = this->getSmallestNode();
    Node<Key, Value>* second = t2.getSmallestNode();

    if(first->getKey() == second->getKey())
    {
        while(first != NULL && second != NULL)
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
void rotateBST<Key,Value>::transformHelper1(rotateBST& t2) const
{
    while(t2.mRoot->getLeft() != NULL)
    {
        t2.rightRotate(t2.mRoot);
    }
}

template<typename Key, typename Value>
Node<Key,Value>* rotateBST<Key,Value>::transformHelper2(rotateBST& t2, Node<Key,Value>* curr) const
{
    Node<Key,Value>* temp = curr;

    while(temp->getLeft() != NULL )
    {    
        t2.rightRotate(temp);
        temp = temp->getParent();
    }

    return temp;   
}

template<typename Key, typename Value>
void rotateBST<Key,Value>::transformHelper3(rotateBST& t2, Node<Key,Value>* left, Node<Key,Value>* right,
	Node<Key,Value>* t_left,Node<Key,Value>* t_right)const
{
    if(left != NULL)
    {
        while(t_left->getKey() != left->getKey())
        {
            t2.rightRotate(left);
            left = left->getParent();
        }

        transformHelper3(t2,left->getLeft(),left->getRight(),t_left->getLeft(),t_left->getRight());
    }

    if(right != NULL)
    {
        while(t_right->getKey() != right->getKey())
        {
            t2.leftRotate(right);
            right = right->getParent();
        }

        transformHelper3(t2,right->getLeft(),right->getRight(),t_right->getLeft(),t_right->getRight());
    }
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{
    if(sameKeys(t2))
    {
        transformHelper1(t2);

        Node<Key,Value>* temp = t2.mRoot->getRight();
        while(temp != NULL )
        {
            temp = transformHelper2(t2,temp);
            if(temp->getLeft()==NULL)
            {
                temp = temp->getRight();
            }   
        }

        while(this->mRoot->getKey() != t2.mRoot->getKey())
        {    
            t2.leftRotate(t2.mRoot);
        }
        
        transformHelper3(t2, t2.mRoot->getLeft(), t2.mRoot->getRight(),this->mRoot->getLeft(),this->mRoot->getRight());
    }
};
#endif
