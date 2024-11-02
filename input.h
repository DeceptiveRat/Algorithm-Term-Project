#pragma once

#include <string>

// shiftMap[valueToKey[x]][y]: value when byte x is shifted y+1 times to the right
extern unsigned char valueToKey[256];

// used for 2~8 bits of input
extern unsigned int shiftMap8bit[7][8];
// used for 9+ bits of input
extern unsigned int shiftMapByte[9][8];

extern unsigned short bitTable[8];

// structures
struct ITEM
{
    ITEM();
    ~ITEM();

    // x = width, y = length, z = height
    int x, y, z, weight;

    int bagNumber, xLocation, yLocation, zLocation;
};

struct BAG
{
    BAG();
    ~BAG();

	// copy constructors
	BAG(const BAG& other);

	// copy assignment
	BAG& operator=(const BAG& other);

    int x, y, z, maxCapacity;
    int itemCount;
	int itemWeightSum;

    unsigned char *map;

    // call after x, y, z is set
    void initMap();

    // saves the maps to a txt file
    void printItemMap(ITEM itemToPrint, std::string fileName);
    void printBagMap(std::string fileName);

    /*
     * Return value: true if item was added to list, false if item wasn't added because there was no space
     */
    bool tryItem(ITEM itemToCheck);
    void putIn(const ITEM itemToInclude, const int bitShifts, const unsigned char *itemMap);
};

// functions
void getInput();

// sort by bag volume descending
void sort(BAG* bags, const int bagCount);
// returns 0 if the first bag has bigger volume 1 otherwise
int compare(const BAG& bag1, const BAG& bag2);
