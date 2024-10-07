#include <iostream>

#include "input.h"

// 생성자와 파괴자
// constructors and destructors
ITEM::ITEM()
{
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
	bagNumber=0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

ITEMLIST::ITEMLIST(ITEM itemToInclude)
{
	ITEM *item = new ITEM;
	*item = itemToInclude;

	nextItem=nullptr;
}

ITEMLIST::~ITEMLIST()
{
	delete item;
}

BAG::BAG()
{
	
};

BAG::~BAG()
{
    x = 0;
    y = 0;
    z = 0;
    maxCapacity = 0;
};

bool BAG::putIn(ITEM itemToCheck)
{
	ITEMLIST* currentPtr;
	currentPtr = itemsInside;

	//check all items in the list to see if there is room
	for(int i=0;i<itemCount;++i)
	{
		// how do I decide where to put it?
		if(itemToCheck.
	}
		
	return true;
};

void getInput()
{
	// 
}
