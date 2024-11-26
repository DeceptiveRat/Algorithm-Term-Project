#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_BAGS 10
#define MAX_HEIGHT 100

// 물건
typedef struct
{
    int width;
    int length;
    int height;
    int weight;
    int number; // index
} Item;

// 가방
typedef struct
{
    int width;
    int length;
    int height;
    char name[20]; // 가방 이름
    int volume;
} Bag;

// 채워진 가방 상태를 저장
typedef struct
{
    int space[100][100][100]; // 3D array to represent the bag space (0 : 빈 공간, 양수 : 물건 번호)
    int used_volume;          // 사용된 부피
    float usage_rate;         // 사용률(%)
} PackedBag;

// Function to compare items by volume for sorting ; 물건을 부피 순으로 정렬 (큰 부피부터)
int compareItems(const void *a, const void *b)
{
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    int volA = itemA->width * itemA->length * itemA->height;
    int volB = itemB->width * itemB->length * itemB->height;
    return volB - volA; // Sort in descending order
}

// Function to compare bags by volume ; 가방을 부피 순으로 정렬 - 오름차순 (작은 부피부터)
int compareBags(const void *a, const void *b)
{
    Bag *bagA = (Bag *)a;
    Bag *bagB = (Bag *)b;
    return bagA->volume - bagB->volume; // Sort in ascending order
}

// Function to check if an item can be placed at a specific position
// 특정 위치에 물건을 넣을 수 있는지 확인
int canPlace(PackedBag *packedBag, int x, int y, int z, Item item, Bag bag)
{
    // 가방 크기를 벗어나는가?
    if (x + item.width > bag.width || y + item.length > bag.length || z + item.height > bag.height)
    {
        return 0;
    }

    // 바닥이 아닌 경우(z > 0), 아래에 지지대가 있는지 확인
    if (z > 0)
    {
        int hasSupport = 0;
        // 물건의 바닥 면적 전체를 확인
        for (int i = x; i < x + item.width; i++)
        {
            for (int j = y; j < y + item.length; j++)
            {
                // 아래층(z-1)에 물건이 있는지 확인
                if (packedBag->space[i][j][z - 1] != 0)
                {
                    hasSupport = 1;
                    break;
                }
            }
            if (hasSupport)
                break;
        }
        // 지지대가 없으면 물건을 놓을 수 없음
        if (!hasSupport)
        {
            return 0;
        }
    }

    // 해당 공간에 다른 물건이 있는가?
    for (int i = x; i < x + item.width; i++)
    {
        for (int j = y; j < y + item.length; j++)
        {
            for (int k = z; k < z + item.height; k++)
            {
                if (packedBag->space[i][j][k] != 0)
                {
                    return 0; // 이미 물건이 존재하는 경우
                }
            }
        }
    }
    return 1; // 물건을 놓을 수 있는 경우
}

// Function to place an item in the bag ; 가방에 물건을 실제로 배치하기
void placeItem(PackedBag *packedBag, int x, int y, int z, Item item)
{
    // 3차원 공간에 물건 번호를 표시
    for (int i = x; i < x + item.width; i++)
    {
        for (int j = y; j < y + item.length; j++)
        {
            for (int k = z; k < z + item.height; k++)
            {
                packedBag->space[i][j][k] = item.number;
            }
        }
    }
    // 사용된 부피 업데이트
    packedBag->used_volume += item.width * item.length * item.height;
}

// Function to find solution A (minimum number of bags) ; 최소 가방 개수
void findMinimumBags(Item *items, int numItems, Bag *bags, int numBags)
{
    // Sort bags by volume (ascending) ; 가방 작은 부피부터 정렬 - Greedy
    qsort(bags, numBags, sizeof(Bag), compareBags);

    // Sort items by volume (descending) ; 물건 부피 큰 것부터 정렬
    qsort(items, numItems, sizeof(Item), compareItems);

    // 각 가방의 packing 상태를 저장하는 배열 할당
    PackedBag *packedBags = (PackedBag *)calloc(numBags, sizeof(PackedBag));
    int currentBag = 0;

    // Try to pack each item
    for (int i = 0; i < numItems; i++)
    {
        int placed = 0;
        while (!placed && currentBag < numBags) // Greedy
        {
            // Try to find a spot in current bag ; 현재 가방의 각 위치에 대해 물건을 놓을 수 있는지 확인
            for (int z = 0; z < bags[currentBag].height && !placed; z++)
            {
                for (int x = 0; x < bags[currentBag].width && !placed; x++)
                {
                    for (int y = 0; y < bags[currentBag].length && !placed; y++)
                    {
                        if (canPlace(&packedBags[currentBag], x, y, z, items[i], bags[currentBag]))
                        {
                            placeItem(&packedBags[currentBag], x, y, z, items[i]);
                            placed = 1;
                            break;
                        }
                    }
                }
            }
            if (!placed) // 현재 가방에 놓을 수 없다면 다음 가방으로
            {
                currentBag++;
            }
        }
    }

    // Print results for each used bag
    for (int b = 0; b <= currentBag; b++)
    {
        if (packedBags[b].used_volume > 0)
        {
            // 사용률 계산
            float usage = (float)packedBags[b].used_volume * 100 /
                          (bags[b].width * bags[b].length * bags[b].height);
            printf("\nBag %s:\n", bags[b].name);
            printf("Usage rate: %.1f%%\n", usage);

            // Print layout for each height level ; 각 높이 별로 배치도를 출력
            for (int h = 0; h < bags[b].height; h++)
            {
                printf("\nLevel: %d\n", h + 1);
                for (int x = 0; x < bags[b].width; x++)
                {
                    for (int y = 0; y < bags[b].length; y++)
                    {
                        if (packedBags[b].space[x][y][h] == 0)
                        {
                            printf("0 "); // 빈 공간
                        }
                        else
                        {
                            printf("%d ", packedBags[b].space[x][y][h]);
                        }
                    }
                    printf("\n");
                }
            }
        }
    }
    free(packedBags);
}

// Function to find solution B (minimum bag size) ; 최소 가방 크기
void findMinimumSize(Item *items, int numItems, Bag *bags, int numBags)
{
    // Sort bags by volume (descending) ; 가방을 큰 부피순으로 정렬
    qsort(bags, numBags, sizeof(Bag), compareBags);
    for (int i = 0; i < numBags / 2; i++)
    {
        Bag temp = bags[i];
        bags[i] = bags[numBags - 1 - i];
        bags[numBags - 1 - i] = temp;
    }

    // Sort items by volume (descending) ; 물건을 큰 부피 순으로 정렬
    qsort(items, numItems, sizeof(Item), compareItems);

    int bestBagIndex = -1;         // 최적의 가방 index
    float bestUsage = 0;           // 최고 사용률
    PackedBag *bestPacking = NULL; // 최적의 packing 상태

    // Try each bag
    for (int b = 0; b < numBags; b++)
    {
        PackedBag currentPacking = {0};
        int allItemsFit = 1; // 모든 물건이 들어가는지 확인

        // Try to pack all items ; 모든 물건을 현재 가방에 넣어보기 - Greedy
        for (int i = 0; i < numItems && allItemsFit; i++)
        {
            int placed = 0;
            // 바닥부터 위로 검사하도록 수정
            for (int z = 0; z < bags[b].height && !placed; z++)
            {
                for (int x = 0; x < bags[b].width && !placed; x++)
                {
                    for (int y = 0; y < bags[b].length && !placed; y++)
                    {
                        if (canPlace(&currentPacking, x, y, z, items[i], bags[b]))
                        {
                            placeItem(&currentPacking, x, y, z, items[i]);
                            placed = 1;
                        }
                    }
                }
            }
            if (!placed)
            {
                allItemsFit = 0; // 하나라도 들어가지 않으면 실패
            }
        }

        // 모든 물건이 들어가는 경우, 사용률 계산
        if (allItemsFit)
        {
            float usage = (float)currentPacking.used_volume * 100 /
                          (bags[b].width * bags[b].length * bags[b].height);

            // 더 좋은 사용률을 찾은 경우, 업데이트 함
            if (usage > bestUsage)
            {
                bestUsage = usage;
                bestBagIndex = b;
                if (bestPacking != NULL)
                {
                    free(bestPacking);
                }
                bestPacking = (PackedBag *)malloc(sizeof(PackedBag));
                memcpy(bestPacking, &currentPacking, sizeof(PackedBag));
            }
        }
    }

    // 최적의 결과 출력
    if (bestBagIndex != -1)
    {
        printf("\nBest bag found: %s\n", bags[bestBagIndex].name);
        printf("Usage rate: %.1f%%\n", bestUsage);

        // Print layout for each height level ; 각 높이별로 배치도 출력
        for (int h = 0; h < bags[bestBagIndex].height; h++)
        {
            printf("\nLevel: %d\n", h);
            for (int x = 0; x < bags[bestBagIndex].width; x++)
            {
                for (int y = 0; y < bags[bestBagIndex].length; y++)
                {
                    if (bestPacking->space[x][y][h] == 0)
                    {
                        printf("0 "); // 빈 공간
                    }
                    else
                    {
                        printf("%d ", bestPacking->space[x][y][h]);
                    }
                }
                printf("\n");
            }
        }
    }
    else
    {
        printf("\nNo suitable bag found that can fit all items.\n");
    }
    if (bestPacking != NULL)
    {
        free(bestPacking);
    }
}

void activateDP()
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
}
