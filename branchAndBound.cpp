#include <iostream>
#include <string>

#include "branchAndBound.h"

NODE::NODE()
{
    bagState = nullptr;
}
NODE::~NODE()
{
    delete[] bagState;
    bagState = nullptr;
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
    item = other.item;
    currentBagUsage = other.currentBagUsage;
    bagCount = other.bagCount;
    initializeBagState(other.bagState, bagCount);
}

NODE& NODE::operator=(const NODE& other)
{
    if(this == &other)
        return *this;

    delete[] bagState;
    bagState = nullptr;

    item = other.item;
    currentBagUsage = other.currentBagUsage;
    bagCount = other.bagCount;
    initializeBagState(other.bagState, bagCount);

    return *this;
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

void QUEUE::push(NODE node)
{
    if(size == capacity)
        throw(std::runtime_error("Queue full!"));

    ++size;
    buffer[++rear] = node;
}

NODE QUEUE::pop()
{
    if(size == 0)
        throw(std::runtime_error("Queue empty so cannot delete!"));

    --size;
    return buffer[front++];
}

bool QUEUE::isEmpty()
{
    if(size == 0)
        return true;

    else
        return false;
}

int bound(const NODE getBoundOf)
{
    return getBoundOf.currentBagUsage;
}

int getMinBagCount(const ITEM* items, const BAG* bags, int itemCount, int bagCount)
{
    QUEUE queue(40, bagCount);
    NODE popped, toPush;

    // current worst case minimum bag usage
    int currentMinBagUsage = itemCount;

    // dummy node
    popped.item = -1;
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
                    // an item was fit into a previously used bag, not a new bag
                    if(toPush.bagState[i].itemCount != 1)
                        toPush.currentBagUsage = popped.currentBagUsage - 1;

                    if(toPush.currentBagUsage + (itemCount - toPush.item) < currentMinBagUsage)
                        currentMinBagUsage = toPush.currentBagUsage + (itemCount - toPush.item);

                    // bounding function
                    if(bound(toPush) <= currentMinBagUsage)
                        queue.push(toPush);
                }
            }
        }

        else
        {
            // print the bag map of each possible outcome
            static int outcome = 0;
            outcome++;

            for(int i = 0; i < bagCount; ++i)
            {
                std::string fileName = "outcome";
                fileName += outcome;
                fileName += " bag";
                fileName += (i + 1);
                popped.bagState[i].printBagMap(fileName);
            }
        }
    }

    return 0;
}
