#include <iostream>
#include <string.h>
// for debugging
#include <fstream>
// for ntohs()
#include <arpa/inet.h>

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
	// deleted in ~BAG()
    map = new unsigned char[size];

    for(int i = 0; i < size; ++i)
        map[i] = 0;

	valueToKey[128] = 0;
	valueToKey[64] = 1;
	valueToKey[32] = 2;
	valueToKey[16] = 3;
	valueToKey[8] = 4;
	valueToKey[4] = 5;
	valueToKey[2] = 6;
	valueToKey[1] = 7;
	valueToKey[192] = 8;
	valueToKey[96] = 9;
	valueToKey[48] = 10;
	valueToKey[24] = 11;
	valueToKey[12] = 12;
	valueToKey[6] = 13;
	valueToKey[3] = 14;
	valueToKey[224] = 15;
	valueToKey[112] = 16;
	valueToKey[56] = 17;
	valueToKey[28] = 18;
	valueToKey[14] = 19;
	valueToKey[7] = 20;
	valueToKey[240] = 21;
	valueToKey[120] = 22;
	valueToKey[60] = 23;
	valueToKey[30] = 24;
	valueToKey[15] = 25;
	valueToKey[248] = 26;
	valueToKey[124] = 27;
	valueToKey[62] = 28;
	valueToKey[31] = 29;
	valueToKey[252] = 30;
	valueToKey[126] = 31;
	valueToKey[63] = 32;
	valueToKey[254] = 33;
	valueToKey[127] = 34;
	valueToKey[255] = 35;
}

void BAG::printItemMap(ITEM itemToCheck)
{
    int itemxBytes = itemToCheck.x / 8;
    unsigned short itemxBits = bitTable[itemToCheck.x % 8];

    std::ofstream output;
	// closed in printItemMap
    output.open("itemMap.txt");

    // buid an array with the item
    int size = (x * y * z - 1) / 8 + 1;
	// deleted in printItemMap()
    itemMap = new unsigned char[size];
    for(int i = 0; i < size; ++i)
        itemMap[i] = 0;

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

	totalBitShift = 0;
	char bitmask = 1<<7;

	// print map
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
}

void BAG::printBagMap()
{
    std::ofstream output;
	// closed in printBagMap
    output.open("bagMap.txt");

	int totalBitShift = 0;

	for(int i =0;i<z;++i)
	{
		output<<"Level: "<<i<<'\n';
		for(int j=0;j<y;++j)
		{
			for(int k=0;k<x;++k)
			{
				output<<((map[totalBitShift/8]>>(7-(totalBitShift%8))) & 1)<<" ";
				++totalBitShift;
			}

			output<<"\n";
		}

		output<<"\n";
	}

	output.close();
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
    int size = (x * y * z - 1) / 8 + 1;
	int totalBitShift = 0;

	// deleted in putIn()
	itemMap = new unsigned char[(x-1)/8+1];

    int itemxBytes = itemToCheck.x / 8;
    unsigned short itemxBits = bitTable[itemToCheck.x % 8];
	unsigned short* ptr;

	for(int k = 0; k < itemxBytes; ++k)
	{
		int bitShiftK = totalBitShift % 8;
		ptr = (unsigned short*)&itemMap[totalBitShift / 8];

		*ptr |= ntohs(0x00ff << (8 - bitShiftK));

		totalBitShift += 8;
	}

	ptr = (unsigned short*)&itemMap[totalBitShift / 8];
	*ptr |= ntohs(itemxBits << (8 - totalBitShift % 8));

	unsigned int *bagMapPtr = (unsigned int*)map;
	unsigned int *itemMapPtr = (unsigned int*)itemMap;

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
			}
		}
	}

	delete[] itemMap;
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
