#include <cstddef>
struct Node
{
    int value;
    Node *next;
};

//Swaps the minimum node with the head node
void swap (Node** head, Node* headLoc, Node* min, Node* MinPrevious)
{
	*head = min;
	MinPrevious->next = headLoc;

	Node* temp = min->next;
	min->next = headLoc->next;
	headLoc->next = temp;
}

//Finds the min comparing it with in node)
Node* FindMin (Node* in, Node* out, Node* min, Node** MinPrevious)
{
	Node* ptr = out;

	//If we reach the end of the list, terminate.
	if (out->next == NULL)
	{
		return min;
	}

	//If new min value is found, reset it
	if (min->value > ptr->next->value)
	{
		min = ptr->next;
		*MinPrevious = ptr;
		min = FindMin (in, out->next, min, MinPrevious);
	}

	else
	{
		min = FindMin (in, out->next, min, MinPrevious);
	}

	return min;
}

Node* fullsort (Node* in)
{
	Node* min = in;
	Node* MinPrevious=NULL;
	Node* ptr = in;

	//If empty list is the input, return NULL
	if (in == NULL)
	{
		return NULL;
	}

	//If we reach the end of the list, return in
	if (in->next == NULL)
	{
		return in;
	}

	else 
	{
		//If new min is found, reset it.
		if (min->value > ptr->next->value)
		{
			min = ptr->next;
			MinPrevious = ptr;
			min = FindMin (in, in->next, min, &MinPrevious);
		}

		else
		{
			min = FindMin(in, in->next, min, &MinPrevious);
		}

		//If min isn't located at the head, then swap
		if (min!=in)
		{
			swap(&in, in, min, MinPrevious);
		}

		in->next = fullsort(in->next);
	}

	return in;
}

