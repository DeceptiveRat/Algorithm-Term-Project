import 'dart:math';

import 'package:flutter/material.dart';
import 'package:get/get.dart';

import 'package:suitcase_uld/controller/view_controller.dart';
import 'package:suitcase_uld/model/bag.dart';
import 'package:suitcase_uld/model/item.dart';
import 'package:suitcase_uld/model/packed_bag.dart';

class Source {
  final ViewController viewController = Get.find();

  RxList<Map<String, dynamic>> result = <Map<String, dynamic>>[].obs;
  RxList<Map<String, dynamic>> resultMinimumNumber =
      <Map<String, dynamic>>[].obs;
  RxList<Map<String, dynamic>> resultMinimumSize = <Map<String, dynamic>>[].obs;

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

  List<Map<String, dynamic>> findBags(List<Item> items, List<Bag> bags,
      {bool sortDescending = true}) {
    bags.sort((a, b) => sortDescending
        ? (b.width * b.height * b.depth).compareTo(a.width * a.height * a.depth)
        : (a.width * a.height * a.depth)
            .compareTo(b.width * b.height * b.depth));

    items.sort((a, b) =>
        (b.width * b.height * b.depth).compareTo(a.width * a.height * a.depth));

    for (int i = 0; i < items.length; i++) {
      items[i].number = i + 1; // 번호 할당
    }

    List<PackedBag> packedBags =
        bags.map((bag) => PackedBag(bag.width, bag.height, bag.depth)).toList();

    for (var item in items) {
      bool placed = false;
      for (int b = 0; b < bags.length && !placed; b++) {
        for (int z = 0; z < bags[b].depth && !placed; z++) {
          for (int x = 0; x < bags[b].width && !placed; x++) {
            for (int y = 0; y < bags[b].height && !placed; y++) {
              if (canPlace(packedBags[b], x, y, z, item, bags[b])) {
                placeItem(packedBags[b], x, y, z, item);
                placed = true;
                print("Item ${item.number} placed in Bag ${b + 1}");
                break;
              }
            }
          }
        }
      }

      if (!placed) {
        print('Error: Could not place item ${item.number}');
      }
    }

    print("Packing Results:");
    packedBags.asMap().forEach((index, bag) {
      print("Bag ${index + 1} used volume: ${bag.usedVolume}");
    });

    return packedBags
        .asMap()
        .entries
        .where((entry) => entry.value.usedVolume > 0)
        .map((entry) {
      final bagIndex = entry.key;
      final packedBag = entry.value;
      final bag = bags[bagIndex];

      double usage =
          packedBag.usedVolume * 100 / (bag.width * bag.height * bag.depth);

      return {
        'name': bag.name,
        'usageRate': usage.toStringAsFixed(1),
        'levels': packedBag.space,
      };
    }).toList();
  }

  void main() {
    List<Item> items = viewController.selectedSuitCaseList;
    List<Bag> bags = viewController.selectedUldList;

    resultMinimumNumber.assignAll(findBags(items, bags, sortDescending: true));
    resultMinimumSize.assignAll(findBags(items, bags, sortDescending: false));
  }
}
