#include <iostream>
#include <string.h>
#include <string>

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

}

void BAG::printItemMap(ITEM itemToCheck, std::string fileName)
{
    int itemxBytes = itemToCheck.x / 8;
    unsigned short itemxBits = bitTable[itemToCheck.x % 8];

    std::ofstream output;
	// closed in printItemMap
    output.open(fileName);

    int size = (x * y * z - 1) / 8 + 1;
	// deleted in printItemMap()
    itemMap = new unsigned char[size];
    for(int i = 0; i < size; ++i)
        itemMap[i] = 0;

    int totalBitShift = 0;

    // used to treat the char array as a short so that we can bitwise or past 1 byte
    unsigned short *ptr;

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

void BAG::printBagMap(std::string fileName)
{
    std::ofstream output;
	// closed in printBagMap
    output.open(fileName);

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

	int totalBitShift = 0;
	int size = (x-1)/8 +1;

	// deleted in putIn()
	itemMap = new unsigned char[size];

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

    int xMaxShift = x - itemToCheck.x;
    int yMaxShift = y - itemToCheck.y;
    int zMaxShift = z - itemToCheck.z;

	if(itemToCheck.x == 1)
	{
		unsigned char byte = 128;

		for(int i = 0;i<zMaxShift;++i)
		{
			for(int j = 0;j<yMaxShift;++j)
			{
				for(int k = 0;k<xMaxShift;++k)
				{
					totalBitShift = (x*y*i + x*j +k);
					
					// fits
					if(map[totalBitShift/8] & (byte>>(totalBitShift%8)) == 0)
					{
						bool fit = true;
						for(int zCheck = 0;zCheck<itemToCheck.z;++zCheck)
						{
							for(int yCheck = 0;yCheck <itemToCheck.y;++yCheck)
							{
								int bitShift = totalBitShift + x*y*zCheck + x*yCheck;
								if(map[bitShift/8] & (byte>>(bitShift%8)) ==0)
									continue;
								else
								{
									// to break both loops
									fit = false;
									zCheck = itemToCheck.z;
									break;
								}
							}
						}

						if(fit)
						{
							// put item into map at this location
							return true;
						}
					}
				}
			}
		}
	}
	else if(itemToCheck.x >8)
	{
		totalBitShift = 0;
		unsigned char byte[2];
		byte[0] = *itemMap;
		byte[1] = itemMap[size-1];

		unsigned char shiftedByte[2];

		for(int i = 0;i<zMaxShift;++i)
		{
			for(int j = 0;j<yMaxShift;++j)
			{
				for(int k = 0;k<xMaxShift;++k)
				{
					totalBitShift = x*y*i + x*j + k;
					unsigned short shiftedBytes = shiftMapByte[valueToKey[byte[0]]][valueToKey[byte[1]]][k];

					shiftedByte[0] = (shiftedBytes&0xff00)>>8;
					shiftedByte[1] = (shiftedBytes&0xff);

					if(map[totalBitShift/8] & shiftedByte[0] == 0)
					{
					}
				}
			}
		}

		delete[] itemMap;
	}

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
