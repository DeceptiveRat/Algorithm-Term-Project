#ifndef DYNAMIC_CODE_H
#define DYNAMIC_CODE_H

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

int compareItems(const void *a, const void *b);
int compareBags(const void *a, const void *b);
int canPlace(PackedBag *packedBag, int x, int y, int z, Item item, Bag bag);
void placeItem(PackedBag *packedBag, int x, int y, int z, Item item);
void findMinimumBags(Item *items, int numItems, Bag *bags, int numBags);
void findMinimumSize(Item *items, int numItems, Bag *bags, int numBags);
void activateDP();

#endif // DYNAMIC_CODE_H