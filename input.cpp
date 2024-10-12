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

void BAG::printItemMap(ITEM itemToPrint, std::string fileName)
{
    int itemxBytes = itemToPrint.x / 8;
    unsigned short itemxBits = bitTable[itemToPrint.x % 8];

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

    for(int i = 0; i < itemToPrint.z; ++i)
    {
        for(int j = 0; j < itemToPrint.y; ++j)
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

bool BAG::tryItem(ITEM itemToCheck)
{
	// check weight limit and return false if it is exceeded

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

		unsigned short shiftedWord[2];

		for(int i = 0;i<zMaxShift;++i)
		{
			for(int j = 0;j<yMaxShift;++j)
			{
				for(int k = 0;k<xMaxShift;++k)
				{
					totalBitShift = x*y*i + x*j + k;
					unsigned short *mapPtr = (unsigned short*)(map+(totalBitShift/8));
					unsigned int shiftedBytes = shiftMapByte[valueToKey[byte[0]]][valueToKey[byte[1]]-8][totalBitShift%8];

					shiftedWord[0] = (shiftedBytes&0xffff0000)>>16;
					shiftedWord[1] = shiftedBytes&0xffff;

					bool fit = true;
					for(int height=0;height<itemToCheck.z;++height)
					{
						totalBitShift+=x*y;

						for(int width=0;width<itemToCheck.y;++width)
						{
							totalBitShift+=x;
							mapPtr = (unsigned short*)(map+(totalBitShift/8));

							// check first 2 bytes ----------------
							// if it doesn't fit, go to shift
							if((*mapPtr & shiftedWord[0]) != 0)
							{
								fit = false;
								height=itemToCheck.z;
								break;
							}

							// check bytes in the middle ---------
							for(int l =2;l<size-1;++l)
							{
								if(map[totalBitShift/8+l] == 0)
									continue;
								else
								{
									// if it doesn't fit in even one place, go to shift
									fit = false;
									height=itemToCheck.z;
									width=itemToCheck.y;
									break;
								}
							}

							// check final 2 bytes -------------
							// exception
							if(size == 2 && (shiftedBytes && 0xff)==0)
							{
								mapPtr = (unsigned short*)(map+(totalBitShift/8 + size));
								if(*mapPtr & shiftedWord[1] == 0)
									continue;
								else
								{
									fit = false;
									height=itemToCheck.z;
									break;
								}
							}

							// other cases
							else
							{
								mapPtr = (unsigned short*)(map+(totalBitShift/8 + size-1));
								if(*mapPtr & shiftedWord[1] == 0)
									continue;
								else
								{
									fit = false;
									height=itemToCheck.z;
									break;
								}
							}
						}
					}
						
					if(fit)
					{
						// put item in this location
						return true;
					}
					else
						continue;
				}
			}
		}
	}

	else
	{
		totalBitShift = 0;
		unsigned char byte[2];
		byte[0] = *itemMap;
		byte[1] = itemMap[size-1];

		for(int i = 0;i<zMaxShift;++i)
		{
			for(int j = 0;j<yMaxShift;++j)
			{
				for(int k = 0;k<xMaxShift;++k)
				{
					totalBitShift = x*y*i + x*j + k;
					unsigned int *mapPtr = (unsigned int*)(map+(totalBitShift/8));
					unsigned int shiftedBytes = shiftMap8bit[valueToKey[byte[0]]][valueToKey[byte[1]]-7][totalBitShift%8];

					bool fit = true;
					for(int height=0;height<itemToCheck.z;++height)
					{
						totalBitShift+=x*y;

						for(int width=0;width<itemToCheck.y;++width)
						{
							totalBitShift+=x;
							mapPtr = (unsigned int*)(map+(totalBitShift/8));

							// check 4 bytes, which is all the bytes for this y and z
							// if it doesn't fit, go to shift
							if((*mapPtr & shiftedBytes) != 0)
							{
								fit = false;
								height=itemToCheck.z;
								break;
							}
						}
					}
						
					if(fit)
					{
						// put item in this location
						return true;
					}
					else
						continue;
				}
			}
		}
	}

	delete[] itemMap;
    return false;
};

void BAG::putIn(ITEM itemToInclude)
{
}

void getInput()
{
    //
}
