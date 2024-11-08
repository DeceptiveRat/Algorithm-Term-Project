#include <iostream>
#include <string>
#include <limits.h>

#include "branchAndBound.h"

#define QUEUESIZE 10000

NODE::NODE()
{
	bagCount = -1;
    bagState = nullptr;
	bagUsage = nullptr;
}
NODE::~NODE()
{
	delete[] bagUsage;
    delete[] bagState;
    bagState = nullptr;
	bagUsage = nullptr;
}

void NODE::initializeBagState(const BAG* listOfBags, int _bagCount)
{
	bagCount = _bagCount;
    // make sure there is only one initialization
    if(bagState != nullptr)
    {
        delete[] bagState;
        bagState = nullptr;
    }

    bagState = new BAG[bagCount];

    for(int i = 0; i < bagCount; i++)
        bagState[i] = listOfBags[i];
}

NODE::NODE(const NODE &other)
{
    bagState = nullptr;
	bagUsage = nullptr;
    item = other.item;
    currentBagUsage = other.currentBagUsage;
    bagCount = other.bagCount;
    initializeBagState(other.bagState, bagCount);

	bagUsage = new bool[bagCount];
	for(int i = 0;i<bagCount;i++)
		bagUsage[i] = other.bagUsage[i];
}

NODE& NODE::operator=(const NODE& other)
{
    if(this == &other)
        return *this;

    delete[] bagState;
    bagState = nullptr;

	delete[] bagUsage;
	bagUsage = nullptr;

    item = other.item;
    currentBagUsage = other.currentBagUsage;
    bagCount = other.bagCount;
    initializeBagState(other.bagState, bagCount);

	bagUsage = new bool[bagCount];
	for(int i = 0;i<bagCount;i++)
		bagUsage[i] = other.bagUsage[i];

    return *this;
}

int NODE::getUsedBagVolume()
{
	int sum = 0;
	for(int i = 0;i<bagCount;i++)
	{
		if(bagUsage[i])
			sum += bagState[i].getVolume();
	}

	return sum;
}

QUEUE::QUEUE(int _capacity, int _bagCount)
{
    buffer = new NODE[_capacity];

    bagCount = _bagCount;
    capacity = _capacity;
    front = 0;
    rear = -1;
    size = 0;
}

QUEUE::~QUEUE()
{
    delete[] buffer;
    buffer = nullptr;

    front = 0;
    rear = 0;
    size = 0;
    capacity = 0;
}

void QUEUE::push(NODE& node)
{
    if(size == capacity)
        throw(std::runtime_error("Queue full!"));

    ++size;
	++rear;
    buffer[rear%QUEUESIZE] = node;
}

NODE& QUEUE::pop()
{
    if(size == 0)
        throw(std::runtime_error("Queue empty so cannot delete!"));

    --size;
    return buffer[(front++)%QUEUESIZE];
}

bool QUEUE::isEmpty()
{
    if(size == 0)
        return true;

    else
        return false;
}

int bound(const NODE &getBoundOf)
{
    return getBoundOf.currentBagUsage;
}

int getMinBagCount(const ITEM* items, const BAG* bags, int itemCount, int bagCount)
{
    QUEUE queue(QUEUESIZE, bagCount);
    NODE popped, toPush;

    // current worst case minimum bag usage
    int currentMinBagUsage = itemCount;

	// smallest bag volume
	int smallestBagVolume = INT_MAX;

    // dummy node
    popped.item = -1;
	popped.bagUsage = new bool[bagCount];
	for(int i = 0;i<bagCount;i++)
		popped.bagUsage[i] = false;
    popped.currentBagUsage = currentMinBagUsage;
    popped.initializeBagState(bags, bagCount);
    queue.push(popped);

    while(!queue.isEmpty())
    {
        popped = queue.pop();
        if(popped.item != itemCount - 1)
        {
            // try putting current item into each bag or none of them
            // if their bounds are greater than the current minimum bag count, don't push
            for(int i = 0; i < bagCount; i++)
            {
                toPush = popped;
                toPush.item = popped.item + 1;

                bool wasPutIn;
                wasPutIn = toPush.bagState[i].tryItem(items[toPush.item]);

                if(wasPutIn)
                {
					toPush.bagUsage[i] = true;
                    // an item was fit into a previously used bag, not a new bag
                    if(toPush.bagState[i].getItemCount() != 1)
                        toPush.currentBagUsage = popped.currentBagUsage - 1;

                    if(toPush.currentBagUsage + (itemCount - 1 - toPush.item) < currentMinBagUsage)
                        currentMinBagUsage = toPush.currentBagUsage + (itemCount - 1 - toPush.item);

                    // bounding function
                    if(bound(toPush) <= currentMinBagUsage)
                        queue.push(toPush);

					if(toPush.getUsedBagVolume() < smallestBagVolume && (toPush.item == itemCount -1))
						smallestBagVolume = toPush.getUsedBagVolume();
                }
            }
        }

        else
        {
            // print the bag map of each possible outcome
            static int outcome = 0;
			if(popped.getUsedBagVolume() != smallestBagVolume)
				continue;

            outcome++;

            for(int i = 0; i < bagCount; ++i)
            {
                std::string fileName = "outcome";
                fileName += std::to_string(outcome);
                fileName += " bag";
                fileName += std::to_string(i + 1);
                popped.bagState[i].printBagMap(fileName+".txt");

				popped.bagState[i].printItemInfo(fileName+"itemInfo.txt");
            }
        }
    }

    return 0;
}
