#include <stdio.h>
#include "dp.h"

#define MAX_ITEMS 100
#define MAX_BAGS 10
#define MAX_HEIGHT 100

int main(void)
{
    // 물건과 가방 배열 선언
    Item items[MAX_ITEMS];
    // 기본 가방 정보 초기화
    Bag bags[MAX_BAGS] = {
        {46, 27, 72, "AB bag", 0},
        {35, 21, 51, "BB bag", 0},
        {15, 13, 20, "Cross bag", 0}};
    int numBags = 3;

    // Calculate volumes for initial bags ; 초기 가방들의 부피 계산
    for (int i = 0; i < numBags; i++)
    {

        bags[i].volume = bags[i].width * bags[i].length * bags[i].height;
    }

    // Get items from user
    printf("Enter number of items: ");
    int numItems;
    scanf("%d", &numItems);

    for (int i = 0; i < numItems; i++)
    {
        printf("\nItem %d:\n", i + 1);
        printf("Width: ");
        scanf("%d", &items[i].width);
        printf("Length: ");
        scanf("%d", &items[i].length);
        printf("Height: ");
        scanf("%d", &items[i].height);
        printf("Weight: ");
        scanf("%d", &items[i].weight);
        items[i].number = i + 1;
    }

    // Option to add new bag
    printf("\nDo you want to add a new bag? (1:Yes/0:No): ");
    int addBag;
    scanf("%d", &addBag);

    if (addBag)
    {
        printf("Enter new bag dimensions:\n");
        printf("Width: ");
        scanf("%d", &bags[numBags].width);
        printf("Length: ");
        scanf("%d", &bags[numBags].length);
        printf("Height: ");
        scanf("%d", &bags[numBags].height);
        sprintf(bags[numBags].name, "New Bag");
        bags[numBags].volume = bags[numBags].width * bags[numBags].length * bags[numBags].height;
        numBags++;
    }

    printf("\nSolution A (Minimum number of bags):\n");
    findMinimumBags(items, numItems, bags, numBags);

    printf("\nSolution B (Minimum bag size):\n");
    findMinimumSize(items, numItems, bags, numBags);

    return 0;
}