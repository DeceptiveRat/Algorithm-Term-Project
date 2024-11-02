#include <iostream>

#include "input.h"
#include "defineTable.h"
#include "branchAndBound.h"

#define INPUTSIZE 2

int main()
{
    // ======================= 임시로 입력 고정 =====================================
    int inputSize = INPUTSIZE;

    // bag init
    int bagx[INPUTSIZE], bagy[INPUTSIZE], bagz[INPUTSIZE], bagCap[INPUTSIZE];

    bagx[0] = 20;
    bagy[0] = 30;
    bagz[0] = 10;
    bagCap[0] = 30;

    bagx[1] = 30;
    bagy[1] = 40;
    bagz[1] = 20;
    bagCap[1] = 40;

/*
    bagx[2] = 40;
    bagy[2] = 50;
    bagz[2] = 30;
    bagCap[2] = 45;

    bagx[3] = 50;
    bagy[3] = 60;
    bagz[3] = 40;
    bagCap[3] = 40;
*/

    BAG* bags = new BAG[inputSize];

    for(int i = 0; i < inputSize; ++i)
    {
		bags[i].setAttribute(bagx[i], bagy[i], bagz[i], bagCap[i]);
		bags[i].initMap();
    }

    // item init
    int xinputs[INPUTSIZE], yinputs[INPUTSIZE], zinputs[INPUTSIZE], weightInputs[INPUTSIZE];

    xinputs[0] = 4;
    yinputs[0] = 8;
    zinputs[0] = 4;
    weightInputs[0] = 10;

    xinputs[1] = 7;
    yinputs[1] = 3;
    zinputs[1] = 7;
    weightInputs[1] = 23;

/*
    xinputs[2] = 3;
    yinputs[2] = 4;
    zinputs[2] = 1;
    weightInputs[2] = 4;

    xinputs[3] = 13;
    yinputs[3] = 15;
    zinputs[3] = 9;
    weightInputs[3] = 103;
*/

    ITEM* items = new ITEM[inputSize];

    for(int i = 0; i < inputSize; ++i)
    {
        items[i].x = xinputs[i];
        items[i].y = yinputs[i];
        items[i].z = zinputs[i];
        items[i].weight = weightInputs[i];
    }

    // ===============================================================================

    // get input

	// sort
	sort(bags, INPUTSIZE);

    // put into greedy

    // put into dp

    // put into B&B
	getMinBagCount(items, bags, inputSize, inputSize);

    // free whole ITEMLIST
    delete[] bags;
    delete[] items;

    return 0;
}
