#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int width;
    int height;
    int depth;
    int weight;
} Item;

typedef struct {
    int width;
    int height;
    int depth;
    int weight_limit;
} Bag;

int min(int a, int b) {
    return a < b ? a : b;
}

int calculate_volume(Bag bag) {
    return bag.width * bag.height * bag.depth;
}

int can_fit(Item item, Bag bag) {
    return item.width <= bag.width && item.height <= bag.height && item.depth <= bag.depth && item.weight <= bag.weight_limit;
}

// 물건을 가방에 배치하는 함수
void place_item_in_bag(int ***bag_space, int bag_width, int bag_height, int bag_depth, Item item, int item_index) {
    for (int i = 0; i < item.height; i++) {
        for (int j = 0; j < item.width; j++) {
            for (int k = 0; k < item.depth; k++) {
                bag_space[i][j][k] = item_index;
            }
        }
    }
}

// 3차원 배열 생성 및 초기화 함수
int ***create_3d_array(int width, int height, int depth) {
    int ***array = (int ***)malloc(height * sizeof(int **));
    for (int i = 0; i < height; i++) {
        array[i] = (int **)malloc(width * sizeof(int *));
        for (int j = 0; j < width; j++) {
            array[i][j] = (int *)malloc(depth * sizeof(int));
            memset(array[i][j], 0, depth * sizeof(int)); // 0으로 초기화
        }
    }
    return array;
}

// 3차원 배열 출력 함수
void print_3d_array(int ***array, int width, int height, int depth) {
    for (int k = 0; k < depth; k++) {
        printf("층 %d:\n", k + 1);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                printf("%d ", array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void free_3d_array(int ***array, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
}

void solve_dp(Item items[], int n, Bag bags[], int m) {
    int INF = INT_MAX;
    int min_bags_count = INF, min_volume_count = INF;
    int ***best_bag_placement_min_count = NULL;
    int ***best_bag_placement_min_volume = NULL;
    int total_weight = 0;

    for (int i = 0; i < n; i++) {
        total_weight += items[i].weight;
    }

    // 최소 개수 기준 배치
    for (int i = 0; i < m; i++) {
        if (bags[i].weight_limit >= total_weight) {
            int ***bag_space = create_3d_array(bags[i].width, bags[i].height, bags[i].depth);
            int bag_volume = calculate_volume(bags[i]);
            int used_bags_count = 0;
            int current_weight = 0;

            for (int j = 0; j < n; j++) {
                if (can_fit(items[j], bags[i])) {
                    place_item_in_bag(bag_space, bags[i].width, bags[i].height, bags[i].depth, items[j], j + 1);
                    current_weight += items[j].weight;
                    used_bags_count++;
                }
            }

            if (current_weight >= total_weight) {
                if (used_bags_count < min_bags_count) {
                    min_bags_count = used_bags_count;
                    if (best_bag_placement_min_count != NULL) {
                        free_3d_array(best_bag_placement_min_count, bags[i].width, bags[i].height);
                    }
                    best_bag_placement_min_count = bag_space;
                } else {
                    free_3d_array(bag_space, bags[i].width, bags[i].height);
                }
            } else {
                free_3d_array(bag_space, bags[i].width, bags[i].height);
            }
        }
    }

    // 최소 크기 기준 배치
    for (int i = 0; i < m; i++) {
        if (bags[i].weight_limit >= total_weight) {
            int ***bag_space = create_3d_array(bags[i].width, bags[i].height, bags[i].depth);
            int bag_volume = calculate_volume(bags[i]);
            int used_bags_volume = 0;
            int current_weight = 0;

            for (int j = 0; j < n; j++) {
                if (can_fit(items[j], bags[i])) {
                    place_item_in_bag(bag_space, bags[i].width, bags[i].height, bags[i].depth, items[j], j + 1);
                    current_weight += items[j].weight;
                    used_bags_volume++;
                }
            }

            if (current_weight >= total_weight) {
                if (bag_volume < min_volume_count) {
                    min_volume_count = bag_volume;
                    if (best_bag_placement_min_volume != NULL) {
                        free_3d_array(best_bag_placement_min_volume, bags[i].width, bags[i].height);
                    }
                    best_bag_placement_min_volume = bag_space;
                } else {
                    free_3d_array(bag_space, bags[i].width, bags[i].height);
                }
            } else {
                free_3d_array(bag_space, bags[i].width, bags[i].height);
            }
        }
    }

    if (min_bags_count == INF) {
        printf("0\n");
    } else {
        printf("최소 가방 개수 사용: %d, 가방 종류: %d, 물건 배치:\n", min_bags_count, min_bags_count);
        print_3d_array(best_bag_placement_min_count, bags[0].width, bags[0].height, bags[0].depth);
        free_3d_array(best_bag_placement_min_count, bags[0].width, bags[0].height);
    }

    if (min_volume_count == INF) {
        printf("0\n");
    } else {
        printf("최소 크기 사용: %d, 가방 종류: %d, 물건 배치:\n", min_volume_count, min_volume_count);
        print_3d_array(best_bag_placement_min_volume, bags[0].width, bags[0].height, bags[0].depth);
        free_3d_array(best_bag_placement_min_volume, bags[0].width, bags[0].height);
    }
}

int main() {
    int n, m;

    printf("물건의 개수: ");
    scanf("%d", &n);
    Item items[n];
    for (int i = 0; i < n; i++) {
        printf("물건 %d의 크기(가로, 세로, 높이)와 무게: ", i + 1);
        scanf("%d %d %d %d", &items[i].width, &items[i].height, &items[i].depth, &items[i].weight);
    }

    printf("가방의 개수: ");
    scanf("%d", &m);
    Bag bags[m];
    for (int i = 0; i < m; i++) {
        printf("가방 %d의 크기(가로, 세로, 높이)와 무게 제한: ", i + 1);
        scanf("%d %d %d %d", &bags[i].width, &bags[i].height, &bags[i].depth, &bags[i].weight_limit);
    }

    solve_dp(items, n, bags, m);

    return 0;
}
