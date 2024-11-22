#include <iostream>
#include "greedy.h"
#include <algorithm>

// 아이템을 부피 기준으로 내림차순 정렬
bool compareItemsByVolume(const ITEM& a, const ITEM& b) {
    return (a.x * a.y * a.z) > (b.x * b.y * b.z);
}

// 가방 개수를 최소화하는 그리디 알고리즘
void getMinBagCountGreedy(ITEM* items, BAG* bags, int itemCount, int bagCount) {
    std::sort(items, items + itemCount, compareItemsByVolume);

    for (int i = 0; i < itemCount; ++i) {
        bool placed = false;

        for (int j = 0; j < bagCount; ++j) {
            if (bags[j].tryItem(items[i])) {
                placed = true;
                break;
            }
        }

        if (!placed) {
            std::cout << "아이템 " << i + 1 << "을(를) 어떤 가방에도 넣을 수 없습니다.\n";
        }
    }

    for (int i = 0; i < bagCount; ++i) {
        std::string filename = "bag_map_" + std::to_string(i + 1) + ".txt";
        bags[i].printBagMap(filename);
    }
}

// 작은 가방을 우선 사용하는 그리디 알고리즘
void prioritizeSmallBagsGreedy(ITEM* items, BAG* bags, int itemCount, int bagCount) {
    std::sort(bags, bags + bagCount, [](const BAG& a, const BAG& b) {
        return a.getVolume() < b.getVolume();
        });

    for (int i = 0; i < itemCount; ++i) {
        bool placed = false;

        for (int j = 0; j < bagCount; ++j) {
            if (bags[j].tryItem(items[i])) {
                placed = true;
                break;
            }
        }

        if (!placed) {
            std::cout << "아이템 " << i + 1 << "을(를) 어떤 가방에도 넣을 수 없습니다.\n";
        }
    }

    for (int i = 0; i < bagCount; ++i) {
        std::string filename = "bag_map_" + std::to_string(i + 1) + ".txt";
        bags[i].printBagMap(filename);
    }
}
