#include "lliststr.h"
 /**
   * Default constructor
   */
  LListStr::LListStr()
  {
  	head_ = NULL;
  	tail_ = NULL;
  	size_ = 0;
  }

  /**
   * Destructor
   */
  LListStr::~LListStr()
	{
		Item* next = head_;
		Item* temp = head_;
		for (int i=0; i<size_; i++)
		{
			next = next->next;
			delete temp;
			temp = next;
		}
		
	}	

  /**
   * Returns the current number of items in the list
   */
  int LListStr::size() const
  {
  	return size_;
  }

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool LListStr::empty() const
  {
  	if(head_ == NULL)
  	{
  		return true;
  	}

  	else
  	{
  		return false;
  	}
  }

  /**
   * Inserts val so it appears at the index given as pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void LListStr::insert(int pos, const std::string &val)
  {
  	//When the index pos is invalid
  	if (pos>size_ || pos < 0)
  	{
  		return;
  	}

  	//When the list is empty
  	if (head_ == NULL)
  	{
  		Item* new_head = new Item;
  		new_head->val = val;
  		new_head->prev = new_head;
  		new_head->next = new_head; 
  		tail_ = new_head;
  		head_ = new_head;
  		++size_;
  		return;
  	}

  	//When inserting at the end
  	if (pos == size_)
  	{
  		Item* new_item = new Item;
  	
  		new_item->val = val;

  		new_item->next = head_;
  		head_->prev = new_item;
  		new_item->prev = tail_;
  		tail_->next = new_item;
  		
  		tail_ = new_item;
  		++size_;
  		return;
  	}

  	//When inserting in the front
  	if (pos == 0)
  	{
  		Item* new_item = new Item;

  		new_item->val = val;

  		new_item->next = head_;
  		new_item->prev = tail_;
  		tail_->next = new_item;
  		head_->prev = new_item;

  		head_ = new_item;
  		++size_;
  		return;
  	}

  	//When inserting in the middle
  	else
  	{
  		Item* new_item = new Item;
  		new_item->val = val;

  		Item* temp = head_;

  		for (int i=1; i<pos; i++)
  		{
  			temp = temp->next;
  		}

  		Item* next_item = temp->next;
  		temp->next = new_item;
  		new_item->prev = temp;
  		new_item->next = next_item;
  		next_item->prev = new_item;

  		++size_;
  		return;
  	}

  }

  /**
   * Removes the value at the index given by pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void LListStr::remove(int pos)
  {
  	//When the index pos is invalid
  	if (pos>(size_-1) || pos < 0)
  	{
  		return;
  	}

  	//When the list is empty
  	if (head_==NULL)
  	{
  		return;
  	}

    //When the list only has one item
    if (size_==1)
    {
      Item* temp = head_;
      head_=NULL;

      delete temp;
      --size_;
      return;
    }

  	//When deleting item with index of 0
  	if (pos == 0)
  	{
  		Item* temp = head_;
  		Item* next_item = head_->next;

  		tail_->next = next_item;
  		next_item->prev = tail_;

  		head_ = next_item;

  		delete temp;
  		--size_;
  		return;
  	}

  	//When deleting item at the end
  	if (pos == size_-1)
  	{
  		Item* temp = tail_;
  		Item* prev_item = tail_->prev;

  		prev_item->next = head_;
  		head_->prev = prev_item;

  		tail_ = prev_item;

  		delete temp;
  		--size_;
  		return;
  	}

  	//When deleting item in the middle
  	else
  	{
  		Item* temp = head_;
  		Item* next_item;
  		Item* prev_item;

  		for (int i=1; i<pos; i++)
  		{
  			temp = temp->next;
  		}
  		next_item = temp->next;
  		prev_item = temp->prev;

  		prev_item->next = next_item;
  		next_item->prev = prev_item;

  		delete temp;
  		--size_;
  		return;
  	}
  }

  /**
   * Overwrites the old value at the index given by pos with val. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void LListStr::set(int pos, const std::string &val)
  {
  	if (pos>size_-1 || pos < 0)
  	{
  		return;
  	}

  	if (head_ == NULL)
  	{
  		return;
  	}

  	else
  	{
  		Item* target = head_;

  		for (int i=0; i<pos; i++)
  		{
  			target = target->next;
  		}

  		target->val = val;
  		return;
  	}

  }

  /**
   * Returns the value at the index given by pos.  If the index pos is invalid,
   * then you should return the empty string.
   */
  std::string LListStr::get(int pos) const
  {
  	if (pos>size_-1 || pos < 0)
  	{
  		return"";
  	}

  	if(head_==NULL)
  	{
  		return "";
  	}

  	else
  	{
  		Item* target = head_;

  		for (int i=0; i<pos; i++)
  		{
  			target = target->next;
  		}
  		return target->val;

  	}
  }