// import 'package:get/get.dart';
// import 'package:suitcase_uld/algorithm/greedy_dp/packed_bag.dart';
// import 'package:suitcase_uld/controller/view_controller.dart';
// import 'package:suitcase_uld/model/item.dart';

// int compareItems(Item a, Item b) => b.volume - a.volume;
// int compareBags(Item a, Item b) => a.volume - b.volume;
// int number = 1;

// class GreedyDPController2 {
//   final ViewController viewController = Get.find();
//   var result = "".obs; // 결과를 저장하는 observable 변수
//   var uldInfo = "".obs; // uld의 종류와 Usage rate를 저장하는 observable 변수

//   bool canPlace(PackedBag packedBag, int x, int y, int z, Item item, Item bag) {
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
//           if (packedBag.space[i][j][k] != 0) return false;
//         }
//       }
//     }
//     return true;
//   }

//   void placeItem(PackedBag packedBag, int x, int y, int z, Item item) {
//     for (int i = x; i < x + item.width; i++) {
//       for (int j = y; j < y + item.height; j++) {
//         for (int k = z; k < z + item.depth; k++) {
//           packedBag.space[i][j][k] = number;
//         }
//       }
//     }
//     packedBag.usedVolume += item.volume;
//     number += 1;
//   }

//   String findMinimumBags(List<Item> items, List<Item> bags) {
//     bags.sort(compareBags);
//     items.sort(compareItems);

//     List<PackedBag> packedBags = List.generate(bags.length,
//         (i) => PackedBag(bags[i].width, bags[i].height, bags[i].depth));

//     int currentBag = 0;
//     StringBuffer resultBuffer = StringBuffer(); // 결과를 저장할 StringBuffer
//     StringBuffer uldInfoBuffer =
//         StringBuffer(); // uld 종류와 Usage rate를 저장할 StringBuffer

//     for (Item item in items) {
//       bool placed = false;
//       while (!placed && currentBag < bags.length) {
//         for (int z = 0; z < bags[currentBag].depth && !placed; z++) {
//           for (int x = 0; x < bags[currentBag].width && !placed; x++) {
//             for (int y = 0; y < bags[currentBag].height && !placed; y++) {
//               if (canPlace(
//                   packedBags[currentBag], x, y, z, item, bags[currentBag])) {
//                 placeItem(packedBags[currentBag], x, y, z, item);
//                 packedBags[currentBag].updateUsageRate(bags[currentBag].volume);
//                 placed = true;
//               }
//             }
//           }
//         }
//         if (!placed) currentBag++;
//       }
//     }

//     for (int b = 0; b <= currentBag; b++) {
//       if (packedBags[b].usedVolume > 0) {
//         uldInfoBuffer.writeln(
//             'Bag ${bags[b].name}: Usage rate ${packedBags[b].usageRate.toStringAsFixed(1)}%');

//         // resultBuffer.writeln('\nBag ${bags[b].name}:');
//         // resultBuffer.writeln(
//         // 'Usage rate: ${packedBags[b].usageRate.toStringAsFixed(1)}%')

//         for (int h = 0; h < bags[b].depth; h++) {
//           resultBuffer.writeln("\nDepth ${h + 1}cm:");
//           for (int x = 0; x < bags[b].width; x++) {
//             String row = "";
//             for (int y = 0; y < bags[b].height; y++) {
//               row += packedBags[b].space[x][y][h] == 0
//                   ? "0"
//                   : "${packedBags[b].space[x][y][h]}";
//             }
//             resultBuffer.writeln(row); // 각 row를 StringBuffer에 추가
//           }
//         }
//       }
//     }

//     uldInfo.value = uldInfoBuffer.toString(); // uld 종류와 Usage rate를 저장
//     return resultBuffer.toString(); // 결과를 하나의 문자열로 반환
//   }

//   void main() {
//     List<Item> items = viewController.selectedSuitCaseList;
//     List<Item> bags = viewController.selectedUldList;

//     if (items.isEmpty || bags.isEmpty) {
//       result.value = "Error: Items or bags list is empty.";
//       return;
//     }

//     result.value = findMinimumBags(items, bags); // 결과를 저장
//     print(result.value); // 결과 확인용 디버그 출력
//     print(uldInfo.value); // uld 종류와 Usage rate 출력

//     number = 1;
//   }
// }

///

// import 'package:get/get.dart';
// import 'package:suitcase_uld/controller/view_controller.dart';
// import 'package:suitcase_uld/model/item.dart';

// import '../../model/packed_bag.dart';

// int compareItems(Item a, Item b) => b.volume - a.volume;
// int compareBags(Item a, Item b) => a.volume - b.volume;
// int number = 1;

// class GreedyDPController2 {
//   final ViewController viewController = Get.find();
//   var result = "".obs; // 결과를 저장하는 observable 변수
//   var uldInfo = "".obs; // uld의 종류와 Usage rate를 저장하는 observable 변수

//   bool canPlace(PackedBag packedBag, int x, int y, int z, Item item, Item bag) {
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
//           if (packedBag.space[i][j][k] != 0) return false;
//         }
//       }
//     }
//     return true;
//   }

//   void placeItem(PackedBag packedBag, int x, int y, int z, Item item) {
//     for (int i = x; i < x + item.width; i++) {
//       for (int j = y; j < y + item.height; j++) {
//         for (int k = z; k < z + item.depth; k++) {
//           packedBag.space[i][j][k] = number;
//         }
//       }
//     }
//     packedBag.usedVolume += item.volume;
//     number += 1;
//   }

//   String findMinimumBags(List<Item> items, List<Item> bags) {
//     if (items.isEmpty || bags.isEmpty) {
//       return "Error: Items or bags list is empty.";
//     }

//     bags.sort(compareBags);
//     items.sort(compareItems);

//     List<PackedBag> packedBags = List.generate(
//       bags.length,
//       (i) => PackedBag(bags[i].width, bags[i].height, bags[i].depth),
//     );

//     int currentBag = 0;
//     StringBuffer resultBuffer = StringBuffer();
//     StringBuffer uldInfoBuffer = StringBuffer();
//     List<Item> failedItems = [];

//     for (Item item in items) {
//       bool placed = false;

//       while (!placed) {
//         // Ensure `currentBag` does not exceed the number of bags
//         if (currentBag >= bags.length) {
//           failedItems.add(item);
//           break;
//         }

//         PackedBag currentPackedBag = packedBags[currentBag];
//         Item currentBagItem = bags[currentBag];

//         for (int z = 0; z < currentBagItem.depth && !placed; z++) {
//           for (int x = 0; x < currentBagItem.width && !placed; x++) {
//             for (int y = 0; y < currentBagItem.height && !placed; y++) {
//               if (canPlace(currentPackedBag, x, y, z, item, currentBagItem)) {
//                 placeItem(currentPackedBag, x, y, z, item);
//                 currentPackedBag.updateUsageRate(currentBagItem.volume);
//                 placed = true;
//               }
//             }
//           }
//         }

//         if (!placed) {
//           currentBag++;
//         }
//       }
//     }

//     for (int b = 0; b < packedBags.length; b++) {
//       PackedBag packedBag = packedBags[b];
//       if (packedBag.usedVolume > 0) {
//         uldInfoBuffer.writeln(
//             'Bag ${bags[b].name}: Usage rate ${packedBag.usageRate.toStringAsFixed(1)}%');

//         for (int h = 0; h < bags[b].depth; h++) {
//           resultBuffer.writeln("\nDepth ${h + 1}cm:");
//           for (int x = 0; x < bags[b].width; x++) {
//             String row = "";
//             for (int y = 0; y < bags[b].height; y++) {
//               row += packedBag.space[x][y][h] == 0
//                   ? "0"
//                   : "${packedBag.space[x][y][h]}";
//             }
//             resultBuffer.writeln(row);
//           }
//         }
//       }
//     }

//     if (failedItems.isNotEmpty) {
//       resultBuffer.writeln("\nFailed to place the following items:");
//       for (var item in failedItems) {
//         resultBuffer.writeln(
//             "${item.name} (size: ${item.width}x${item.height}x${item.depth})");
//       }
//     }

//     uldInfo.value = uldInfoBuffer.toString();
//     return resultBuffer.toString();
//   }

//   void main() {
//     List<Item> items = viewController.selectedSuitCaseList;
//     List<Item> bags = viewController.selectedUldList;

//     if (items.isEmpty || bags.isEmpty) {
//       result.value = "Error: Items or bags list is empty.";
//       return;
//     }

//     result.value = findMinimumBags(items, bags); // 결과를 저장
//     print(result.value); // 결과 확인용 디버그 출력
//     print(uldInfo.value); // uld 종류와 Usage rate 출력

//     number = 1;
//   }
// }
