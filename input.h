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
	ITEMLIST();
	~ITEMLIST();

	// copy operators
	ITEMLIST(const ITEMLIST& other);
	ITEMLIST& operator=(const ITEMLIST& other);

	void addItemToList(const ITEM itemToInclude);
	// deletes item and all the items after this in the list
	// **warning** doesn't delete itself so it must be manually deleted
	void deleteList();

	ITEM* item;
	ITEMLIST* nextItemOnList;
};

struct BAG
{
public:
    BAG();
    ~BAG();

	// copy operators
	BAG(const BAG& other);
	BAG& operator=(const BAG& other);

	/* getters and setters */
	int getVolume() const;
	int getItemCount() const;
	void setAttribute(const int _x, const int _y, const int _z, const int _maxCapacity);

	/* insert item */
	// true if able to put in
    bool tryItem(ITEM itemToCheck);
    void putIn(const ITEM itemToInclude, const int bitShifts, const unsigned char *itemMap);
	void addItemToBag(const ITEM &itemToAdd);

	/* map */
    // call after x, y, z is set
    void initMap();
    // saves the maps to a txt file
    void printItemMap(ITEM itemToPrint, std::string fileName);
    void printBagMap(std::string fileName);

private:
	/* basic attributes */
    int x, y, z, maxCapacity;
    int itemCount;
	int itemWeightSum;

	/* itemlist */
	ITEMLIST* firstItemPtr;
	ITEMLIST* lastItemPtr;

    unsigned char *map;
};

// functions
void getInput();

// sort by bag volume descending
void sort(BAG* bags, const int bagCount);
// returns 0 if the first bag has bigger volume 1 otherwise
int compare(const BAG& bag1, const BAG& bag2);
