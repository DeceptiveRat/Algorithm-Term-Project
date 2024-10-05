#pragma once

// 구조
// structures
struct ITEM
{
    ITEM(int _x, int _y, int _z, int _weight);
    ~ITEM();

    // x = 폭, y = 너비, z = 높이
    // x = width, y = length, z = height
    int x;
    int y;
    int z;

    int weight;

    int xLocation;
    int yLocation;
    int zLocation;
};

struct BAG
{
    BAG(int _x, int _y, int _z, int _maxCapacity);
    ~BAG();

    int x;
    int y;
    int z;

    int maxCapacity;

    int xLocation;
    int yLocation;
    int zLocation;
};

struct ITEMLIST
{
	ITEMLIST(ITEM* _item);
	~ITEMLIST();

	ITEM* item;
	ITEMLIST* nextItem;
};

// 함수
// functions
void getInput();
