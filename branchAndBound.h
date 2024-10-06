#pragma once

#include "input.h"

// node for the state space tree
struct NODE
{
	// item on the list, as well as the level of the tree
	int level;

	// total weight until now
	int weight;
	
	// lower bound for bag count
	int bagBound;

	// need to keep track of each of the bags so we can choose where to put it in
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

int bound();
int getMinBagCount(const ITEM* items, const BAG* bags, int itemCount);
void mergeSort();
void merge();
