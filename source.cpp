#include <iostream>

#include "input.h"
#include "defineTable.h"
#include "branchAndBound.h"

#define BAGCOUNT 3
#define ITEMCOUNT 6

int main()
{
	// DO NOT REMOVE!
	initTables();

    // ======================= 임시로 입력 고정 =====================================
    int bagCount = BAGCOUNT;
	int itemCount = ITEMCOUNT;

    // bag init
    int bagx[BAGCOUNT], bagy[BAGCOUNT], bagz[BAGCOUNT], bagCap[BAGCOUNT];

    bagx[0] = 3;
    bagy[0] = 2;
    bagz[0] = 2;
    bagCap[0] = 40;

    bagx[1] = 5;
    bagy[1] = 3;
    bagz[1] = 3;
    bagCap[1] = 40;

    bagx[2] = 10;
    bagy[2] = 4;
    bagz[2] = 4;
    bagCap[2] = 45;

/*
    bagx[3] = 50;
    bagy[3] = 60;
    bagz[3] = 40;
    bagCap[3] = 40;
*/

    BAG* bags = new BAG[bagCount];

    for(int i = 0; i < bagCount; ++i)
    {
		bags[i].setAttribute(bagx[i], bagy[i], bagz[i], bagCap[i]);
		bags[i].initMap();
    }

    // item init
    int xinputs[ITEMCOUNT], yinputs[ITEMCOUNT], zinputs[ITEMCOUNT], weightInputs[ITEMCOUNT];

    xinputs[0] = 1;
    yinputs[0] = 2;
    zinputs[0] = 2;
    weightInputs[0] = 1;

    xinputs[1] = 2;
    yinputs[1] = 2;
    zinputs[1] = 2;
    weightInputs[1] = 2;

    xinputs[2] = 3;
    yinputs[2] = 3;
    zinputs[2] = 3;
    weightInputs[2] = 3;

    xinputs[3] = 2;
    yinputs[3] = 3;
    zinputs[3] = 3;
    weightInputs[3] = 2;

    xinputs[4] = 5;
    yinputs[4] = 4;
    zinputs[4] = 4;
    weightInputs[4] = 1;

    xinputs[5] = 5;
    yinputs[5] = 4;
    zinputs[5] = 4;
    weightInputs[5] = 3;

/*
    xinputs[6] = 10;
    yinputs[6] = 30;
    zinputs[6] = 10;
    weightInputs[6] = 40;

    xinputs[7] = 15;
    yinputs[7] = 15;
    zinputs[7] = 16;
    weightInputs[7] = 20;
*/

    ITEM* items = new ITEM[itemCount];

    for(int i = 0; i < itemCount; ++i)
    {
        items[i].x = xinputs[i];
        items[i].y = yinputs[i];
        items[i].z = zinputs[i];
        items[i].weight = weightInputs[i];
    }

    // ===============================================================================

    // get input

	// sort
	sort(bags, BAGCOUNT);

    // put into greedy

    // put into dp

    // put into B&B
	getMinBagCount(items, bags, itemCount, bagCount);

    // free whole ITEMLIST
    delete[] bags;
    delete[] items;

    return 0;
}
