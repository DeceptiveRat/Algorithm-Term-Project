#include <iostream>
#include <string.h>
#include <string>

// for debugging
#include <fstream>
// for ntohs()
#include <arpa/inet.h>

#include "input.h"

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

BAG::BAG()
{
    map = nullptr;
};

BAG::~BAG()
{
    x = 0;
    y = 0;
    z = 0;
    maxCapacity = 0;
    delete[] map;
    map = nullptr;
};

BAG::BAG(const BAG& other)
{
    map = nullptr;
    x = other.x;
    y = other.y;
    z = other.z;
    maxCapacity = other.maxCapacity;
    itemCount = other.itemCount;
    itemWeightSum = other.itemWeightSum;
    initMap();
}

BAG& BAG::operator=(const BAG& other)
{
    if(this == &other)
        return *this;

    // delete resources
    delete[] map;
    map = nullptr;

    // copy
    x = other.x;
    y = other.y;
    z = other.z;
    maxCapacity = other.maxCapacity;
    itemCount = other.itemCount;
    itemWeightSum = other.itemWeightSum;
    initMap();

    return *this;
}

// do only once
void BAG::initMap()
{
    // if there is already a value, delete after alerting user
    if(map != nullptr)
    {
        printf("deleted map before adding new map!\n");
        printf("This is not supposed to happen!\n");
        delete[] map;
        map = nullptr;
    }

    int size = (x * y * z - 1) / 8 + 1;
    map = new unsigned char[size];

    for(int i = 0; i < size; ++i)
        map[i] = 0;

}

void BAG::printItemMap(ITEM itemToPrint, std::string fileName)
{
    int itemxBytes = itemToPrint.x / 8;
    unsigned short itemxBits = bitTable[itemToPrint.x % 8];

    std::ofstream output;
    output.open(fileName);

    // map of the item to print
    unsigned char* itemMap;
    int size = (x * y * z - 1) / 8 + 1;
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

                *ptr |= ntohs((short)(0x00ff << (8 - bitShiftK)));

                totalBitShift += 8;
            }

            ptr = (unsigned short*)&itemMap[totalBitShift / 8];
            // need to convert to big endian
            *ptr |= ntohs((short)(itemxBits << (8 - totalBitShift % 8)));
        }
    }

    totalBitShift = 0;

    // print map
    for(int i = 0; i < z; ++i)
    {
        output << "Level: " << i << '\n';

        for(int j = 0; j < y; ++j)
        {
            for(int k = 0; k < x; ++k)
            {
                output << ((itemMap[totalBitShift / 8] >> (7 - (totalBitShift % 8))) & 1) << " ";
                ++totalBitShift;
            }

            output << "\n";
        }

        output << "\n";
    }

    delete[] itemMap;
    output.close();
}

void BAG::printBagMap(std::string fileName)
{
    std::ofstream output;
    output.open(fileName);

    int totalBitShift = 0;

    for(int i = 0; i < z; ++i)
    {
        output << "Level: " << i << '\n';

        for(int j = 0; j < y; ++j)
        {
            for(int k = 0; k < x; ++k)
            {
                output << ((map[totalBitShift / 8] >> (7 - (totalBitShift % 8))) & 1) << " ";
                ++totalBitShift;
            }

            output << "\n";
        }

        output << "\n";
    }

    output.close();
}

bool BAG::tryItem(ITEM itemToCheck)
{
    // check weight limit and return false if it is exceeded
    if(itemWeightSum + itemToCheck.weight > maxCapacity)
        return false;

    int totalBitShift = 0;
    int itemSize = (itemToCheck.x - 1) / 8 + 1;

    unsigned char *itemMap;
    itemMap = new unsigned char[itemSize];

    int itemxBytes = itemToCheck.x / 8;
    unsigned short itemxBits = bitTable[itemToCheck.x % 8];
    unsigned short* ptr;

    for(int k = 0; k < itemxBytes; ++k)
    {
        int bitShiftK = totalBitShift % 8;
        ptr = (unsigned short*)&itemMap[totalBitShift / 8];

        *ptr = ntohs((short)(0x00ff << (8 - bitShiftK)));

        totalBitShift += 8;
    }

    ptr = (unsigned short*)&itemMap[totalBitShift / 8];
    *ptr = ntohs((short)(itemxBits << (8 - totalBitShift % 8)));

    int xMaxShift = x - itemToCheck.x;
    int yMaxShift = y - itemToCheck.y;
    int zMaxShift = z - itemToCheck.z;

    if(itemToCheck.x == 1)
    {
        unsigned char byte = 128;

        for(int i = 0; i <= zMaxShift; ++i)
        {
            for(int j = 0; j <= yMaxShift; ++j)
            {
                for(int k = 0; k <= xMaxShift; ++k)
                {
                    totalBitShift = (x * y * i + x * j + k);

                    // fits
                    if(map[totalBitShift / 8] & ((byte >> (totalBitShift % 8)) == 0))
                    {
                        bool fit = true;

                        for(int height = 0; height < itemToCheck.z; ++height)
                        {
                            for(int width = 0; width < itemToCheck.y; ++width)
                            {
                                int bitShift = totalBitShift + x * y * height + x * width;

                                if(map[bitShift / 8] & ((byte >> (bitShift % 8)) == 0))
                                    continue;

                                else
                                {
                                    // to break both loops
                                    fit = false;
                                    height = itemToCheck.z;
                                    break;
                                }
                            }
                        }

                        if(fit)
                        {
                            putIn(itemToCheck, totalBitShift, itemMap);
                            itemCount++;
                            itemWeightSum += itemToCheck.weight;
                            return true;
                        }
                    }
                }
            }
        }
    }

    else if(itemToCheck.x > 8)
    {
        totalBitShift = 0;
        unsigned char byte;
        byte = itemMap[itemSize - 1];

        unsigned short shiftedWord[2];

        for(int i = 0; i <= zMaxShift; ++i)
        {
            for(int j = 0; j <= yMaxShift; ++j)
            {
                for(int k = 0; k <= xMaxShift; ++k)
                {
                    totalBitShift = x * y * i + x * j + k;
                    unsigned short *mapPtr;
                    unsigned int shiftedBytes;
                    bool fit = true;

                    for(int height = 0; height < itemToCheck.z; ++height)
                    {
                        for(int width = 0; width < itemToCheck.y; ++width)
                        {
                            int checkWord = totalBitShift + height * x * y + width * x;
                            mapPtr = (unsigned short*)(map + (checkWord / 8));

                            shiftedBytes = shiftMapByte[valueToKey[byte]][checkWord % 8];
                            shiftedWord[0] = (shiftedBytes & 0xff000000) >> 16;
                            shiftedWord[1] = shiftedBytes & 0xffff;

                            // check first 2 bytes ----------------
                            // if it doesn't fit, go to shift
                            if((*mapPtr & ntohs(shiftedWord[0])) != 0)
                            {
                                fit = false;
                                height = itemToCheck.z;
                                break;
                            }

                            // check bytes in the middle ---------
                            for(int l = 1; l < itemSize - 1; ++l)
                            {
                                if(map[checkWord / 8 + l] == 0)
                                    continue;

                                else
                                {
                                    // if it doesn't fit in even one place, go to shift
                                    fit = false;
                                    height = itemToCheck.z;
                                    width = itemToCheck.y;
                                    break;
                                }
                            }

                            // check final 2 bytes -------------
                            // exception
                            mapPtr = (unsigned short*)(map + (checkWord / 8 + itemSize - 1));

                            if((*mapPtr & ntohs(shiftedWord[1])) == 0)
                                continue;

                            else
                            {
                                fit = false;
                                height = itemToCheck.z;
                                break;
                            }
                        }
                    }

                    if(fit)
                    {
                        putIn(itemToCheck, totalBitShift, itemMap);
                        itemCount++;
                        itemWeightSum += itemToCheck.weight;
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
        unsigned char byte;
        byte = *itemMap;

        for(int i = 0; i <= zMaxShift; ++i)
        {
            for(int j = 0; j <= yMaxShift; ++j)
            {
                for(int k = 0; k <= xMaxShift; ++k)
                {
                    totalBitShift = x * y * i + x * j + k;
                    unsigned int *mapPtr;
                    unsigned int shiftedBytes;

                    bool fit = true;

                    for(int height = 0; height < itemToCheck.z; ++height)
                    {
                        for(int width = 0; width < itemToCheck.y; ++width)
                        {
                            int checkBit = totalBitShift + height * x * y + width * x;
                            mapPtr = (unsigned int*)(map + (checkBit / 8));
                            shiftedBytes = shiftMap8bit[valueToKey[byte]][checkBit % 8];

                            // check 4 bytes, which is all the bytes for this y and z
                            // if it doesn't fit, go to shift
                            if((*mapPtr & ntohl(shiftedBytes)) != 0)
                            {
                                fit = false;
                                height = itemToCheck.z;
                                break;
                            }
                        }
                    }

                    if(fit)
                    {
                        putIn(itemToCheck, totalBitShift, itemMap);
                        itemCount++;
                        itemWeightSum += itemToCheck.weight;
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
}

void BAG::putIn(const ITEM itemToInclude, const int bitShifts, const unsigned char *itemMap)
{
    int totalBitShift = 0;
    int itemSize = (itemToInclude.x - 1) / 8 + 1;

    if(itemToInclude.x == 1)
        for(int zInclude = 0; zInclude < itemToInclude.z; ++zInclude)
        {
            for(int yInclude = 0; yInclude < itemToInclude.y; ++yInclude)
            {
                totalBitShift = bitShifts + x * y * zInclude + x * yInclude;

                // fit the one bit
                map[totalBitShift / 8] |= 128 >> (totalBitShift % 8);
            }
        }

    else if(itemToInclude.x > 8)
    {
        unsigned char byte;
        byte = itemMap[itemSize - 1];

        unsigned short shiftedWord[2];

        totalBitShift = bitShifts;
        unsigned short *mapPtr;
        unsigned int shiftedBytes;

        for(int height = 0; height < itemToInclude.z; ++height)
        {
            for(int width = 0; width < itemToInclude.y; ++width)
            {
                int insertWord = totalBitShift + height * x * y + width * x;
                mapPtr = (unsigned short*)(map + (insertWord / 8));
                shiftedBytes = shiftMapByte[valueToKey[byte]][insertWord % 8];
                shiftedWord[0] = (shiftedBytes & 0xff000000) >> 16;
                shiftedWord[1] = shiftedBytes & 0xffff;

                // insert first word
                *mapPtr |= ntohs(shiftedWord[0]);

                // insert middle bytes
                for(int l = 1; l < itemSize - 1; ++l)
                    map[insertWord / 8 + l] |= 0xff;

                // insert last word
                // exception
                mapPtr = (unsigned short*)(map + (insertWord / 8 + itemSize - 1));

                *mapPtr |= ntohs(shiftedWord[1]);
            }
        }
    }

    else
    {
        totalBitShift = bitShifts;
        unsigned char byte;
        byte = *itemMap;

        unsigned int *mapPtr;
        unsigned int shiftedBytes;

        for(int height = 0; height < itemToInclude.z; ++height)
        {
            for(int width = 0; width < itemToInclude.y; ++width)
            {
                int insertDword = totalBitShift + height * x * y + width * x;
                mapPtr = (unsigned int*)(map + (insertDword / 8));
                shiftedBytes = shiftMap8bit[valueToKey[byte]][insertDword % 8];

                // insert 4 bytes, which is all the bytes for this y and z
                *mapPtr |= ntohl(shiftedBytes);
            }
        }
    }
}

void getInput()
{
    //
}

void sort(BAG* bags, const int bagCount)
{
    BAG tempBag;
    int maxIndex;

    for(int i = 0; i < bagCount; i++)
    {
        maxIndex = i;

        for(int j = i + 1; j < bagCount; j++)
        {
            if(compare(bags[j], bags[maxIndex]) == 0)
                maxIndex = j;
        }

        tempBag = bags[i];
        bags[i] = bags[maxIndex];
        bags[maxIndex] = tempBag;
    }
}

int compare(const BAG& bag1, const BAG& bag2)
{
    if(bag1.x * bag1.y * bag1.z > bag2.x * bag2.y * bag2.z)
        return 0;

    else
        return 1;
}
