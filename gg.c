#include <stdio.h>
#include <stdbool.h>

#define MAX_BAGS 10  // 최대 가방 수
#define MAX_ITEMS 20 // 최대 물건 수

typedef struct
{
    int width, height, depth; // 가방 혹은 물건의 크기
    int volume;               // 부피
    int weight;               // 물건의 무게만 해당
} Item;

// 부피 계산 함수
int calculateVolume(int width, int height, int depth)
{
    return width * height * depth;
}

// DP 배열 및 함수 초기화
int dp[MAX_BAGS][MAX_ITEMS];
int bagVolume[MAX_BAGS];
int bagMinIndex[MAX_BAGS]; // 최소 가방 사용 시 최소 공간이 남는 가방 인덱스 저장용

// 최대 가방 크기 옵션 선택 함수
int findMaxBagOption(Item bags[], int bagCount, Item items[], int itemCount)
{
    int selectedBagIndex = -1;
    int minRemainingVolume = __INT_MAX__; // 가장 작은 빈 공간 추적

    for (int i = 0; i < bagCount; i++)
    {
        int remainingVolume = bagVolume[i];
        int currentVolume = 0;

        // 물건을 가방에 담아보기
        for (int j = 0; j < itemCount; j++)
        {
            if (bags[i].volume >= items[j].volume && remainingVolume >= items[j].volume)
            {
                remainingVolume -= items[j].volume;
                currentVolume += items[j].volume;
            }
        }

        // 최소 빈 공간 갱신
        if (remainingVolume < minRemainingVolume)
        {
            minRemainingVolume = remainingVolume;
            selectedBagIndex = i;
        }
    }
    return selectedBagIndex;
}

// 최소 가방 크기 옵션 선택 함수
int findMinBagOption(Item bags[], int bagCount, Item items[], int itemCount)
{
    int totalVolumeNeeded = 0;

    bool usedBags[MAX_BAGS] = {0}; // 사용된 가방 표시

    for (int i = 0; i < itemCount; i++)
    {
        totalVolumeNeeded += items[i].volume;
    }

    printf("Bags used for minimum bag size option:\n");
    for (int i = 0; i < bagCount; i++)
    {
        if (totalVolumeNeeded <= 0)
            break;

        if (bags[i].volume >= totalVolumeNeeded)
        {
            printf("Bag %d (volume %d)\n", i + 1, bags[i].volume);
            usedBags[i] = true;
            totalVolumeNeeded -= bags[i].volume;
            break;
        }
        else if (bags[i].volume < totalVolumeNeeded)
        {
            printf("Bag %d (volume %d)\n", i + 1, bags[i].volume);
            usedBags[i] = true;
            totalVolumeNeeded -= bags[i].volume;
        }
    }

    if (totalVolumeNeeded > 0)
    {
        printf("Not enough bag space to pack all items.\n");
    }
}

int main()
{
    int bagCount, itemCount;
    Item bags[MAX_BAGS];
    Item items[MAX_ITEMS];

    printf("Enter the number of bags: ");
    scanf("%d", &bagCount);

    // 가방 입력 받기
    for (int i = 0; i < bagCount; i++)
    {
        printf("Enter dimensions for bag %d (width height depth): ", i + 1);
        scanf("%d %d %d", &bags[i].width, &bags[i].height, &bags[i].depth);
        bags[i].volume = calculateVolume(bags[i].width, bags[i].height, bags[i].depth);
        bagVolume[i] = bags[i].volume;
    }

    printf("Enter the number of items: ");
    scanf("%d", &itemCount);

    // 물건 입력 받기
    for (int i = 0; i < itemCount; i++)
    {
        printf("Enter dimensions and weight for item %d (width height depth weight): ", i + 1);
        scanf("%d %d %d %d", &items[i].width, &items[i].height, &items[i].depth, &items[i].weight);
        items[i].volume = calculateVolume(items[i].width, items[i].height, items[i].depth);
    }

    // 최대 가방 크기 옵션 실행
    int maxBagIndex = findMaxBagOption(bags, bagCount, items, itemCount);
    if (maxBagIndex != -1)
    {
        printf("Best option for max bag size is bag %d with minimum remaining space.\n", maxBagIndex + 1);
    }
    else
    {
        printf("No suitable single bag found for all items.\n");
    }

    // 최소 가방 크기 옵션 실행
    int minBagsNeeded = findMinBagOption(bags, bagCount, items, itemCount);
    printf("Minimum bags needed for all items: %d\n", minBagsNeeded);

    return 0;
}
