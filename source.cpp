#include <iostream>

#include "input.h"
#include "defineTable.h"

#define INPUTSIZE 4

int main()
{
    initTables();

    // ======================= 임시로 입력 고정 =====================================
    /*
    int inputSize = INPUTSIZE;

    // bag init
    int bagx[INPUTSIZE], bagy[INPUTSIZE], bagz[INPUTSIZE], bagCap[INPUTSIZE];

    bagx[0] = 20;
    bagx[1] = 30;
    bagx[2] = 40;
    bagx[3] = 50;

    bagy[0] = 30;
    bagy[1] = 40;
    bagy[2] = 50;
    bagy[3] = 60;

    bagz[0] = 10;
    bagz[1] = 20;
    bagz[2] = 30;
    bagz[3] = 40;

    bagCap[0] = 30;
    bagCap[1] = 40;
    bagCap[2] = 45;
    bagCap[3] = 40;

    BAG* bags = new BAG[inputSize];

    for(int i = 0; i < inputSize; ++i)
    {
        bags[i].x = bagx[i];
        bags[i].y = bagy[i];
        bags[i].z = bagz[i];
        bags[i].maxCapacity = bagCap[i];
    }

    // item init
    int xinputs[INPUTSIZE], yinputs[INPUTSIZE], zinputs[INPUTSIZE], weightInputs[INPUTSIZE];

    xinputs[0] = 4;
    xinputs[1] = 7;
    xinputs[2] = 3;
    xinputs[3] = 13;

    yinputs[0] = 8;
    yinputs[1] = 3;
    yinputs[2] = 4;
    yinputs[3] = 15;

    zinputs[0] = 4;
    zinputs[1] = 7;
    zinputs[2] = 1;
    zinputs[3] = 9;

    weightInputs[0] = 10;
    weightInputs[1] = 23;
    weightInputs[2] = 4;
    weightInputs[3] = 103;

    ITEM* items = new ITEM[inputSize];

    for(int i = 0; i < inputSize; ++i)
    {
        items[i].x = xinputs[i];
        items[i].y = yinputs[i];
        items[i].z = zinputs[i];
        items[i].weight = weightInputs[i];
    }

    int a, b;
    std::cin >> a >> b;
    int k = shiftMap8bit[valueToKey[a]][b];
    //int k = shiftMapByte[valueToKey[a]][b];
    std::cout << k << '\n';

    // ===============================================================================

    // 입력받기
    // get input

    // 그리디
    // put into greedy

    // 다이나믹프로그래밍
    // put into dp

    // 브랜치&바운드
    // put into B&B

    // free whole ITEMLIST
    delete[] bags;
    delete[] items;
    */

    BAG testBag;
    testBag.x = 10;
    testBag.y = 9;
    testBag.z = 8;

    ITEM testItem;
    testItem.x = 3;
    testItem.y = 4;
    testItem.z = 5;

    ITEM testItem2;
    testItem2.x = 7;
    testItem2.y = 5;
    testItem2.z = 2;

    ITEM testItem3;
    testItem3.x = 4;
    testItem3.y = 5;
    testItem3.z = 3;

    ITEM testItem4;
    testItem4.x = 10;
    testItem4.y = 3;
    testItem4.z = 4;

    BAG testBag2;
    testBag2.x = 40;
    testBag2.y = 2;
    testBag2.z = 3;

    ITEM testItem5;
    testItem5.x = 30;
    testItem5.y = 1;
    testItem5.z = 2;

    ITEM testItem6;
    testItem6.x = 20;
    testItem6.y = 2;
    testItem6.z = 1;

    ITEM testItem7;
    testItem7.x = 10;
    testItem7.y = 2;
    testItem7.z = 3;

    testBag.initMap();
    testBag2.initMap();

    bool result = testBag.tryItem(testItem);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    result = testBag.tryItem(testItem);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    result = testBag.tryItem(testItem2);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    result = testBag.tryItem(testItem3);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    result = testBag.tryItem(testItem4);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    testBag.printBagMap("test4.txt");

    result = testBag2.tryItem(testItem5);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    result = testBag2.tryItem(testItem6);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    result = testBag2.tryItem(testItem7);

    if(result)
        std::cout << "Success!\n";

    else
        std::cout << "Something went wrong.\n";

    testBag2.printBagMap("test5.txt");

    return 0;
}
