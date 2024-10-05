#include <iostream>

#include "input.h"

// 생성자와 파괴자
// constructors and destructors
ITEM::ITEM(int _x, int _y, int _z, int _weight)
{
    x = _x;
    y = _y;
    z = _z;
    weight = _weight;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

ITEM::~ITEM()
{
    x = 0;
    y = 0;
    z = 0;
    weight = 0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

BAG::BAG(int _x, int _y, int _z, int _maxCapacity)
{
    x = _x;
    y = _y;
    z = _z;
    maxCapacity = _maxCapacity;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

BAG::~BAG()
{
    x = 0;
    y = 0;
    z = 0;
    maxCapacity = 0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

ITEMLIST::ITEMLIST(ITEM* _item)
{
	item=_item;
	nextItem=nullptr;
}

// automatically free item
ITEMLIST::~ITEMLIST()
{
	delete item;
}

void getInput()
{
	// 
}
