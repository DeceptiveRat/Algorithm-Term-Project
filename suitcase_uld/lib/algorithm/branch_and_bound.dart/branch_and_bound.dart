// import 'dart:math';

// import 'package:get/get.dart';
// import 'package:suitcase_uld/controller/view_controller.dart';
// import 'package:suitcase_uld/model/bag.dart';
// import 'package:suitcase_uld/model/item.dart';
// import 'package:suitcase_uld/model/packed_bag.dart';

// class BranchAndBound {
//   final ViewController viewController = Get.find();

//   RxList<Map<String, dynamic>> resultMinimumNumber =
//       <Map<String, dynamic>>[].obs;
//   RxList<Map<String, dynamic>> resultMinimumSize = <Map<String, dynamic>>[].obs;

//   double bestUsage = 0; // 최적 사용률

//   bool canPlace(PackedBag packedBag, int x, int y, int z, Item item, Bag bag) {
//     if (x + item.width > bag.width ||
//         y + item.height > bag.height ||
//         z + item.depth > bag.depth) {
//       return false;
//     }

//     if (z > 0) {
//       bool hasSupport = false;
//       for (int i = x; i < x + item.width; i++) {
//         for (int j = y; j < y + item.height; j++) {
//           if (packedBag.space[i][j][z - 1] != 0) {
//             hasSupport = true;
//             break;
//           }
//         }
//         if (hasSupport) break;
//       }
//       if (!hasSupport) return false;
//     }

//     for (int i = x; i < x + item.width; i++) {
//       for (int j = y; j < y + item.height; j++) {
//         for (int k = z; k < z + item.depth; k++) {
//           if (packedBag.space[i][j][k] != 0) {
//             return false;
//           }
//         }
//       }
//     }

//     return true;
//   }

//   void placeItem(PackedBag packedBag, int x, int y, int z, Item item) {
//     for (int i = x; i < x + item.width; i++) {
//       for (int j = y; j < y + item.height; j++) {
//         for (int k = z; k < z + item.depth; k++) {
//           packedBag.space[i][j][k] = item.number!;
//         }
//       }
//     }
//     packedBag.usedVolume += item.width * item.height * item.depth;
//   }

//   double bound(List<Item> items, List<PackedBag> packedBags, int currentIndex) {
//     double currentUsage =
//         packedBags.fold(0, (sum, bag) => sum + bag.usedVolume);
//     double potentialRemainingUsage = items
//         .sublist(currentIndex)
//         .fold(0, (sum, item) => sum + item.width * item.height * item.depth);

//     return currentUsage + potentialRemainingUsage;
//   }

//   void branchAndBound(List<Item> items, List<Bag> bags, int index,
//       List<PackedBag> packedBags, double currentUsage, bool minimizeBags) {
//     if (index == items.length) {
//       if (currentUsage > bestUsage) {
//         bestUsage = currentUsage;

//         RxList<Map<String, dynamic>> result =
//             minimizeBags ? resultMinimumNumber : resultMinimumSize;

//         result.clear();
//         for (int b = 0; b < packedBags.length; b++) {
//           if (packedBags[b].usedVolume > 0) {
//             final bag = bags[b];
//             final usage = packedBags[b].usedVolume /
//                 (bag.width * bag.height * bag.depth) *
//                 100;

//             result.add({
//               'name': bag.name,
//               'usageRate': usage.toStringAsFixed(1),
//               'levels': packedBags[b].space,
//             });
//           }
//         }
//       }
//       return;
//     }

//     final item = items[index];
//     double currentBound = bound(items, packedBags, index);

//     if (currentBound <= bestUsage) {
//       return; // 가지치기
//     }

//     for (int b = 0; b < bags.length; b++) {
//       for (int z = 0; z < bags[b].depth; z++) {
//         for (int x = 0; x < bags[b].width; x++) {
//           for (int y = 0; y < bags[b].height; y++) {
//             if (canPlace(packedBags[b], x, y, z, item, bags[b])) {
//               final originalUsage = packedBags[b].usedVolume;

//               placeItem(packedBags[b], x, y, z, item);

//               branchAndBound(items, bags, index + 1, packedBags,
//                   currentUsage + packedBags[b].usedVolume, minimizeBags);

//               packedBags[b].usedVolume = originalUsage; // 복원
//             }
//           }
//         }
//       }
//     }
//   }

//   void findOptimalBags(List<Item> items, List<Bag> bags) {
//     items.sort((a, b) =>
//         (b.width * b.height * b.depth).compareTo(a.width * a.height * a.depth));

//     List<PackedBag> packedBags =
//         bags.map((bag) => PackedBag(bag.width, bag.height, bag.depth)).toList();

//     // 최소 가방 개수
//     bestUsage = 0;
//     branchAndBound(items, bags, 0, packedBags, 0, true);

//     // 최소 용량 사용률
//     bestUsage = 0;
//     branchAndBound(items, bags, 0, packedBags, 0, false);
//   }

//   void main() {
//     List<Item> items = viewController.selectedSuitCaseList;
//     List<Bag> bags = viewController.selectedUldList;

//     findOptimalBags(items, bags);

//     print(resultMinimumNumber);
//     print(resultMinimumSize);
//   }
// }

import 'dart:math';

import 'package:get/get.dart';
import 'package:suitcase_uld/controller/view_controller.dart';
import 'package:suitcase_uld/model/bag.dart';
import 'package:suitcase_uld/model/item.dart';
import 'package:suitcase_uld/model/packed_bag.dart';

class BranchAndBound {
  final ViewController viewController = Get.find();

  RxList<Map<String, dynamic>> resultMinimumNumber =
      <Map<String, dynamic>>[].obs;
  RxList<Map<String, dynamic>> resultMinimumSize = <Map<String, dynamic>>[].obs;

  RxList<Map<String, dynamic>> result = <Map<String, dynamic>>[].obs; // 단일 결과값

  double bestUsage = 0; // 최적 사용률

  bool canPlace(PackedBag packedBag, int x, int y, int z, Item item, Bag bag) {
    if (x + item.width > bag.width ||
        y + item.height > bag.height ||
        z + item.depth > bag.depth) {
      return false;
    }

    if (z > 0) {
      bool hasSupport = false;
      for (int i = x; i < x + item.width; i++) {
        for (int j = y; j < y + item.height; j++) {
          if (packedBag.space[i][j][z - 1] != 0) {
            hasSupport = true;
            break;
          }
        }
        if (hasSupport) break;
      }
      if (!hasSupport) return false;
    }

    for (int i = x; i < x + item.width; i++) {
      for (int j = y; j < y + item.height; j++) {
        for (int k = z; k < z + item.depth; k++) {
          if (packedBag.space[i][j][k] != 0) {
            return false;
          }
        }
      }
    }

    return true;
  }

  void placeItem(PackedBag packedBag, int x, int y, int z, Item item) {
    for (int i = x; i < x + item.width; i++) {
      for (int j = y; j < y + item.height; j++) {
        for (int k = z; k < z + item.depth; k++) {
          packedBag.space[i][j][k] = item.number!;
        }
      }
    }
    packedBag.usedVolume += item.width * item.height * item.depth;
  }

  double bound(List<Item> items, List<PackedBag> packedBags, int currentIndex) {
    double currentUsage =
        packedBags.fold(0, (sum, bag) => sum + bag.usedVolume);
    double potentialRemainingUsage = items
        .sublist(currentIndex)
        .fold(0, (sum, item) => sum + item.width * item.height * item.depth);

    return currentUsage + potentialRemainingUsage;
  }

  void branchAndBound(List<Item> items, List<Bag> bags, int index,
      List<PackedBag> packedBags, double currentUsage, bool minimizeBags) {
    if (index == items.length) {
      if (currentUsage > bestUsage) {
        bestUsage = currentUsage;

        RxList<Map<String, dynamic>> targetResult =
            minimizeBags ? resultMinimumNumber : resultMinimumSize;

        targetResult.clear();
        result.clear(); // 단일 결과값도 업데이트

        for (int b = 0; b < packedBags.length; b++) {
          if (packedBags[b].usedVolume > 0) {
            final bag = bags[b];
            final usage = packedBags[b].usedVolume /
                (bag.width * bag.height * bag.depth) *
                100;

            final bagData = {
              'name': bag.name,
              'usageRate': usage.toStringAsFixed(1),
              'levels': packedBags[b].space,
            };

            targetResult.add(bagData); // 각 결과 리스트에 추가
            result.add(bagData); // 단일 결과 리스트에도 추가
          }
        }
      }
      return;
    }

    final item = items[index];
    double currentBound = bound(items, packedBags, index);

    if (currentBound <= bestUsage) {
      return; // 가지치기
    }

    for (int b = 0; b < bags.length; b++) {
      for (int z = 0; z < bags[b].depth; z++) {
        for (int x = 0; x < bags[b].width; x++) {
          for (int y = 0; y < bags[b].height; y++) {
            if (canPlace(packedBags[b], x, y, z, item, bags[b])) {
              final originalUsage = packedBags[b].usedVolume;

              placeItem(packedBags[b], x, y, z, item);

              branchAndBound(items, bags, index + 1, packedBags,
                  currentUsage + packedBags[b].usedVolume, minimizeBags);

              packedBags[b].usedVolume = originalUsage; // 복원
            }
          }
        }
      }
    }
  }

  void findOptimalBags(List<Item> items, List<Bag> bags) {
    items.sort((a, b) =>
        (b.width * b.height * b.depth).compareTo(a.width * a.height * a.depth));

    List<PackedBag> packedBags =
        bags.map((bag) => PackedBag(bag.width, bag.height, bag.depth)).toList();

    // 최소 가방 개수
    bestUsage = 0;
    branchAndBound(items, bags, 0, packedBags, 0, true);

    // 최소 용량 사용률
    bestUsage = 0;
    branchAndBound(items, bags, 0, packedBags, 0, false);

    // 단일 결과를 result로 반환
    result.assignAll(resultMinimumNumber.isNotEmpty
        ? resultMinimumNumber
        : resultMinimumSize);
  }

  void main() {
    List<Item> items = viewController.selectedSuitCaseList;
    List<Bag> bags = viewController.selectedUldList;

    findOptimalBags(items, bags);

    print(result); // 단일 결과 출력
  }
}
