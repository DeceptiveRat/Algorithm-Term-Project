#include <iostream>
#include "input.h"
#include "defineTable.h"
#include "greedy.h"

#define BAGCOUNT 3
#define ITEMCOUNT 8

int main()
{
    // DO NOT REMOVE
    initTables();

    // ======================= 임시로 입력 고정 =====================================
    int bagCount = BAGCOUNT;
    int itemCount = ITEMCOUNT;

    // 가방 초기화
    int bagx[BAGCOUNT] = { 5, 10, 30 };
    int bagy[BAGCOUNT] = { 3, 10, 14 };
    int bagz[BAGCOUNT] = { 3, 10, 14 };
    int bagCap[BAGCOUNT] = { 40, 40, 45 };

    BAG* bags = new BAG[bagCount];
    for (int i = 0; i < bagCount; ++i) {
        bags[i].setAttribute(bagx[i], bagy[i], bagz[i], bagCap[i]);
        bags[i].initMap();
    }

    // 아이템 초기화
    int xinputs[ITEMCOUNT] = { 30, 2, 3, 2, 5, 7, 10, 5 };
    int yinputs[ITEMCOUNT] = { 10, 2, 3, 3, 4, 3, 12, 12 };
    int zinputs[ITEMCOUNT] = { 2, 2, 3, 3, 4, 3, 3, 2 };
    int weightInputs[ITEMCOUNT] = { 1, 2, 3, 2, 1, 3, 1, 20 };

    ITEM* items = new ITEM[itemCount];
    for (int i = 0; i < itemCount; ++i) {
        items[i].x = xinputs[i];
        items[i].y = yinputs[i];
        items[i].z = zinputs[i];
        items[i].weight = weightInputs[i];
    }

    // ======================= 정렬 및 배치 ===========================
    std::cout << "가방 개수를 최소화:\n";
    getMinBagCountGreedy(items, bags, itemCount, bagCount);

    std::cout << "\n작은 가방 우선 사용:\n";
    prioritizeSmallBagsGreedy(items, bags, itemCount, bagCount);

    // 메모리 해제
    delete[] bags;
    delete[] items;

    return 0;
}
