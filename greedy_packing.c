#include <stdio.h>
#include <stdlib.h>
#include "input.h"  // input.h 헤더 파일 포함

// 현실적인 캐리어 크기 및 무게 제한 정의
#define BAG_20_INCH_MAX_VOLUME 44000  // 20인치 가방 부피 (40cm * 55cm * 20cm = 44000cm³)
#define BAG_20_INCH_MAX_WEIGHT 10000  // 20인치 가방 무게 제한 10kg = 10000g

#define BAG_26_INCH_MAX_VOLUME 65000  // 26인치 가방 대략적인 부피 (60 ~ 65L, 약 65000cm³)
#define BAG_26_INCH_MAX_WEIGHT 25000  // 26인치 가방 무게 제한 25kg = 25000g (일반적으로 더 큰 무게 허용)

// 물건의 부피를 계산하는 함수
int calculateVolume(ITEM item) {
    return item.x * item.y * item.z;
}

// 부피 기준 내림차순 정렬 함수 (그리디를 위해 큰 물건부터 처리)
int compareItems(const void* a, const void* b) {
    ITEM* itemA = (ITEM*)a;
    ITEM* itemB = (ITEM*)b;
    
    int volumeA = calculateVolume(*itemA);
    int volumeB = calculateVolume(*itemB);
    
    return volumeB - volumeA;  // 부피가 큰 순서대로 정렬
}

// 가방에 물건을 넣는 함수
bool tryToPutItemInBag(BAG* bag, ITEM* item) {
    int itemVolume = calculateVolume(*item);
    
    // 가방에 남은 공간과 무게가 충분한지 확인
    if (bag->maxCapacity >= itemVolume && bag->remainingWeight >= item->weight) {
        // 아이템을 가방에 넣음
        if (bag->itemsInside == NULL) {
            bag->itemsInside = (ITEMLIST*)malloc(sizeof(ITEMLIST));
            bag->itemsInside->item = item;
            bag->itemsInside->nextItem = NULL;
        } else {
            ITEMLIST* current = bag->itemsInside;
            while (current->nextItem != NULL) {
                current = current->nextItem;
            }
            current->nextItem = (ITEMLIST*)malloc(sizeof(ITEMLIST));
            current->nextItem->item = item;
            current->nextItem->nextItem = NULL;
        }
        
        // 가방의 남은 용량과 무게를 줄임
        bag->maxCapacity -= itemVolume;
        bag->remainingWeight -= item->weight;
        bag->itemCount++;
        return true;
    }
    
    return false;  // 공간이 부족하거나 무게 제한을 초과하면 false 반환
}

// 물건들을 그리디 알고리즘으로 가방에 배치하는 함수
void packItemsInBags(ITEM* items, int itemCount, BAG* bags, int bagCount) {
    // 물건을 부피 기준 내림차순으로 정렬
    qsort(items, itemCount, sizeof(ITEM), compareItems);
    
    // 각 물건을 하나씩 처리
    for (int i = 0; i < itemCount; ++i) {
        ITEM* currentItem = &items[i];
        
        // 각 가방에 물건을 넣을 수 있는지 시도
        for (int j = 0; j < bagCount; ++j) {
            if (tryToPutItemInBag(&bags[j], currentItem)) {
                currentItem->bagNumber = j;  // 물건이 배치된 가방 번호 저장
                break;
            }
        }
    }
}

// 입력 받는 함수 (getInput() 구현)
void getInput(ITEM* items, int* itemCount, BAG* bags, int* bagCount) {
    printf("가방의 개수를 입력하세요: ");
    scanf("%d", bagCount);

    // 가방의 크기를 입력받아 초기화 (20인치 또는 26인치 크기 사용)
    for (int i = 0; i < *bagCount; ++i) {
        printf("가방 %d의 크기를 입력하세요 (20 또는 26): ", i + 1);
        int size;
        scanf("%d", &size);

        if (size == 20) {
            bags[i].maxCapacity = BAG_20_INCH_MAX_VOLUME;
            bags[i].remainingWeight = BAG_20_INCH_MAX_WEIGHT;
        } else if (size == 26) {
            bags[i].maxCapacity = BAG_26_INCH_MAX_VOLUME;
            bags[i].remainingWeight = BAG_26_INCH_MAX_WEIGHT;
        } else {
            printf("잘못된 크기입니다. 기본으로 20인치 가방 설정.\n");
            bags[i].maxCapacity = BAG_20_INCH_MAX_VOLUME;
            bags[i].remainingWeight = BAG_20_INCH_MAX_WEIGHT;
        }
        
        bags[i].itemsInside = NULL;
        bags[i].itemCount = 0;
    }

    // 물건 정보 입력
    printf("물건의 개수를 입력하세요: ");
    scanf("%d", itemCount);
    
    for (int i = 0; i < *itemCount; ++i) {
        printf("물건 %d의 가로(x), 세로(y), 높이(z), 무게(gram)를 입력하세요: ", i + 1);
        scanf("%d %d %d %d", &items[i].x, &items[i].y, &items[i].z, &items[i].weight);
        items[i].bagNumber = -1;  // 초기 상태에서는 가방에 배치되지 않음
    }
}

int main() {
    int bagCount;
    BAG bags[10];  // 최대 10개의 가방
    int itemCount;
    ITEM items[100];  // 최대 100개의 물건
    
    // 입력 받기
    getInput(items, &itemCount, bags, &bagCount);
    
    // 물건을 가방에 배치
    packItemsInBags(items, itemCount, bags, bagCount);
    
    // 결과 출력
    printf("배치 결과:\n");
    for (int i = 0; i < itemCount; ++i) {
        printf("물건 %d: 가방 %d에 배치됨\n", i + 1, items[i].bagNumber + 1);
    }
    
    return 0;
}
