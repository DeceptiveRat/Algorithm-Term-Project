#pragma once

// shiftMap[valueToKey[x]][y]: value when byte x is shifted y+1 times to the right 
extern unsigned char valueToKey[256];
//extern unsigned char shiftMap[36][8];

// shiftMap[valueToKey[x]][valueToKey[y]][z]: value of x shifted by z+1 as the first byte, y shifted by z+1 as second byte
// used for 2~8 bits of input
extern unsigned short shiftMap8bit[36][37][8];
// used for 9+ bits of input
extern unsigned short shiftMapByte[36][36][8];

extern unsigned short bitTable[8];

// 구조
// structures
struct ITEM
{
	ITEM();
    ~ITEM();

    // x = 폭, y = 너비, z = 높이
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

	// experimenting -------------------------------------------------------------------------------------
	// map of the bag in bits. map is allocated contiguously, so no need to worry about array indices
	unsigned char *map;
	unsigned char *itemMap;

	// call after x, y, z is set
	void initMap();

	// saves the maps to a txt file
	void printItemMap(ITEM itemToCheck);
	void printBagMap();


	// ----------------------------------------------------------------------------------------------------

	/*
	 * Return value: true if item was added to list, false if item wasn't added because there was no space
	 */
	bool putIn(ITEM itemToCheck);

	/*
	 * Description: given axis A and length L, find the first location in axis A where L can fit. If there is none, return -1
	 * 				Axis x -> 0, y -> 1, z -> 2
	 */
	int firstAvailableLocation(int axis, int length);
};

// 함수
// functions
void getInput();

// global variable
