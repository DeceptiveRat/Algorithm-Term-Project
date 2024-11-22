#pragma once
#include "input.h"

// 가방 개수를 최소화하는 함수
void getMinBagCountGreedy(ITEM* items, BAG* bags, int itemCount, int bagCount);

// 작은 가방을 우선 사용하는 함수
void prioritizeSmallBagsGreedy(ITEM* items, BAG* bags, int itemCount, int bagCount);
