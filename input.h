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

struct ITEMLIST
{
    ITEMLIST(ITEM itemToInclude);
    ~ITEMLIST();

    ITEM* item;
    ITEMLIST* nextItem;
};

struct BAG
{
    BAG();
    ~BAG();

    int x, y, z, maxCapacity;

    ITEMLIST* itemsInside;
    int itemCount;

    unsigned char *map;
    unsigned char *itemMap;

    // call after x, y, z is set
    void initMap();

    // saves the maps to a txt file
    void printItemMap(ITEM itemToPrint, std::string fileName);
    void printBagMap(std::string fileName);

    /*
     * Return value: true if item was added to list, false if item wasn't added because there was no space
     */
    bool tryItem(ITEM itemToCheck);
    void putIn(const ITEM itemToInclude, const int bitShifts);
};

// 함수
// functions
void getInput();
