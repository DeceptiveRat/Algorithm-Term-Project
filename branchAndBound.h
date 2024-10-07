#pragma once

#include "input.h"

// node for the state space tree
struct NODE
{
	// item on the list, as well as the level of the tree
	int level;

	// need to keep track of each of the bags so we can choose where to put it in
	BAG* bagState;
	
	// lower bound for bag count
	int bagBound;
};

struct QUEUE
{
	QUEUE(int _capacity);
	~QUEUE();

	NODE* buffer;
	int capacity;
	int size;
	int front;
	int rear;

	void push(NODE node);
	NODE pop();
	bool isEmpty();
};

int bound(BAG* bagState, int level);
int getMinBagCount(const ITEM* items, const BAG* bags, int itemCount);
void mergeSort();
void merge();
