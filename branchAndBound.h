#pragma once

#include "input.h"

// node for the state space tree
struct NODE
{
	NODE();
	~NODE();
	// item on the list, as well as the level of the tree
	int item;

	// need to keep track of each of the bags so we can choose where to put it in
	BAG* bagState;
	
	// lower bound for bag count
	int currentBagUsage;
	int bagCount;

	// input a list of sorted bags, and their state
	// return false if something went wrong
	void initializeBagState(const BAG* listOfBags, int bagCount);

	// copy constructor
	NODE(const NODE &other);

	// copy assignment operator
	NODE& operator=(const NODE& other);
};

struct QUEUE
{
	QUEUE(int _capacity, int _bagCount);
	~QUEUE();

	QUEUE(const QUEUE&) = delete;
	QUEUE& operator=(const QUEUE&) = delete;

	NODE* buffer;
	int capacity;
	int size;
	int front;
	int rear;
	int bagCount;

	void push(NODE node);
	NODE pop();
	bool isEmpty();
};

int bound(const NODE getBoundOf);
int getMinBagCount(const ITEM* items, const BAG* bags, int itemCount, int bagCount);
