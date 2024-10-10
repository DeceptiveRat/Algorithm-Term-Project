#pragma once

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

	unsigned short bitTable[8] = {0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe};

	// uses too much space for each bag. See if I can move it out to a global variable. Also, see if I can do something about all the redundant values in shiftMap
	// shiftMap[valueToKey[x]][y]: value when byte x is shifted y+1 times to the right 
	unsigned char valueToKey[256];
	unsigned char shiftMap[36][8] = {
	64, 32, 16, 8, 4, 2, 1, 0,
	32, 16, 8, 4, 2, 1, 0, 0,
	16, 8, 4, 2, 1, 0, 0, 0,
	8, 4, 2, 1, 0, 0, 0, 0,
	4, 2, 1, 0, 0, 0, 0, 0,
	2, 1, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	96, 48, 24, 12, 6, 3, 1, 0,
	48, 24, 12, 6, 3, 1, 0, 0,
	24, 12, 6, 3, 1, 0, 0, 0,
	12, 6, 3, 1, 0, 0, 0, 0,
	6, 3, 1, 0, 0, 0, 0, 0,
	3, 1, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	112, 56, 28, 14, 7, 3, 1, 0,
	56, 28, 14, 7, 3, 1, 0, 0,
	28, 14, 7, 3, 1, 0, 0, 0,
	14, 7, 3, 1, 0, 0, 0, 0,
	7, 3, 1, 0, 0, 0, 0, 0,
	3, 1, 0, 0, 0, 0, 0, 0,
	120, 60, 30, 15, 7, 3, 1, 0,
	60, 30, 15, 7, 3, 1, 0, 0,
	30, 15, 7, 3, 1, 0, 0, 0,
	15, 7, 3, 1, 0, 0, 0, 0,
	7, 3, 1, 0, 0, 0, 0, 0,
	124, 62, 31, 15, 7, 3, 1, 0,
	62, 31, 15, 7, 3, 1, 0, 0,
	31, 15, 7, 3, 1, 0, 0, 0,
	15, 7, 3, 1, 0, 0, 0, 0,
	126, 63, 31, 15, 7, 3, 1, 0,
	63, 31, 15, 7, 3, 1, 0, 0,
	31, 15, 7, 3, 1, 0, 0, 0,
	127, 63, 31, 15, 7, 3, 1, 0,
	63, 31, 15, 7, 3, 1, 0, 0,
	127, 63, 31, 15, 7, 3, 1, 0	};

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
