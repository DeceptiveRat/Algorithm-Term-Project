#include <iostream>
#include <string.h>
// for debugging
#include <fstream>
// for ntohs()
#include <arpa/inet.h>

#include "input.h"

unsigned short bitTable[8] = {0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe};

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
    bagNumber = 0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

ITEMLIST::ITEMLIST(ITEM itemToInclude)
{
    ITEM *item = new ITEM;
    *item = itemToInclude;

    nextItem = nullptr;
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
    delete[] map;
};

void BAG::initMap()
{
    int size = (x * y * z - 1) / 8 + 1;
    map = new unsigned char[size];

    for(int i = 0; i < size; ++i)
        map[i] = 0;
}

bool BAG::putIn(ITEM itemToCheck)
{
    /*
    	ITEMLIST* currentPtr;
    	currentPtr = itemsInside;

    	//check all items in the list to see if there is room
    	for(int i=0;i<itemCount;++i)
    	{
    		if(itemToCheck.x
    	}
    */

    // experimenting -------------------------------------------------------------------------------------
    int itemxBytes = itemToCheck.x / 8;
    unsigned short itemxBits = bitTable[itemToCheck.x % 8];

    std::ofstream output;
    output.open("itemMap.txt");

    // buid an array with the item
    int size = (x * y * z - 1) / 8 + 1;
    itemMap = new unsigned char[size];

    for(int i = 0; i < size; ++i)
        itemMap[i] = 0;

    // total bit shift variable for quicker calculation
    int totalBitShift = 0;

    // used to treat the char array as a short so that we can bitwise or past 1 byte
    unsigned short *ptr;

    // create item map
    for(int i = 0; i < itemToCheck.z; ++i)
    {
        for(int j = 0; j < itemToCheck.y; ++j)
        {
            totalBitShift = x * j + x * y * i;

            for(int k = 0; k < itemxBytes; ++k)
            {
                int bitShiftK = totalBitShift % 8;
                ptr = (unsigned short*)&itemMap[totalBitShift / 8];

                *ptr |= ntohs(0x00ff << (8 - bitShiftK));

                totalBitShift += 8;
            }

            ptr = (unsigned short*)&itemMap[totalBitShift / 8];
            // need to convert to big endian
            *ptr |= ntohs(itemxBits << (8 - totalBitShift % 8));
        }
    }

	/*
    unsigned int *itemMapPtr = (unsigned int*)itemMap;
	unsigned int *bagMapPtr = (unsigned int*)map;

	// set up parameters that will be used
    int xMaxShift = x - itemToCheck.x;
    int yMaxShift = y - itemToCheck.y;
    int zMaxShift = z - itemToCheck.z;
	int mapPtrMaxIndex = size/4;

	for(int i = 0;i<zMaxShift;++i)
	{
		for(int j = 0;j<yMaxShift;++j)
		{
			for(int k = 0;k<xMaxShift;++k)
			{
				totalBitShift = (x*y*z + x*j +k);

			}
		}
	}
	*/

    	totalBitShift = 0;
    	char bitmask = 1<<7;

    	// print for debugging purposes
    	for(int i =0;i<z;++i)
    	{
    		output<<"Level: "<<i<<'\n';
    		for(int j=0;j<y;++j)
    		{
    			for(int k=0;k<x;++k)
    			{
    				output<<((itemMap[totalBitShift/8]>>(7-(totalBitShift%8))) & 1)<<" ";
    				++totalBitShift;
    			}

    			output<<"\n";
    		}

    		output<<"\n";
    	}

    delete[] itemMap;
    output.close();

    return true;
};

int BAG::firstAvailableLocation(int axis, int length)
{
    /*
    	if(axis==0)
    	{

    	}
    	else if(axis==1)
    	else if(axis==2)
    	else
    	{
    		return -1;
    	}
    */

    // experimenting -------------------------------------------------------------------------------------
    return 0;
}

void getInput()
{
    //
}
