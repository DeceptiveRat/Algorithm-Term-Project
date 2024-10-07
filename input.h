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

	/*
	 * Return value: true if item was added to list, false if item wasn't added because there was no space
	 */
	bool putIn(ITEM itemToCheck);

};

// 함수
// functions
void getInput();
