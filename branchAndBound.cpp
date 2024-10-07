#include <iostream>

#include "branchAndBound.h"

QUEUE::QUEUE(int _capacity)
{
	buffer = new NODE[_capacity];
	capacity = _capacity;
	front=0;
	rear=-1;
	size = 0;
}

QUEUE::~QUEUE()
{
	front =0;
	rear=0;
	size=0;
	capacity=0;
	delete[] buffer;
}

void QUEUE::push(NODE node)
{
	if(size==capacity)
		throw(std::runtime_error("Queue full!"));
	
	++size;
	buffer[++rear]= node;
}

NODE QUEUE::pop()
{
	if(size==0)
		throw(std::runtime_error("Queue empty so cannot delete!"));
	
	--size;
	return buffer[front++];
}

bool QUEUE::isEmpty()
{
	if(size==0)
		return true;
	else
		return false;
}

int bound(BAG* bagState, int level)
{
	return 0;
}

int getMinBagCount(const ITEM* items, const BAG* bags, int itemCount)
{
	// sort bags by capacity descending and save to a new list
	
	QUEUE queue(10);	
	NODE popped, toPush;

	// dummy node
	popped.level=-1;
	popped.bagState = nullptr;
	popped.bagBound=500;
	queue.push(popped);

	int minBagCount=500;
	while(!queue.isEmpty())
	{
		popped = queue.pop();
		
		// if last node
		if(popped.level == itemCount-1)
			continue;
		else
			toPush.level = popped.level+1;

		// try putting current item into each bag or none of them
		// if their bounds are greater than the current minimum bag count, don't push
	}

	return 0;
}
