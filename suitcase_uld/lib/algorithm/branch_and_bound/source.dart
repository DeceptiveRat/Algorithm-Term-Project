// Dart translation of source.cpp

import 'package:suitcase_uld/algorithm/branch_and_bound/branch_and_bound.dart';
import 'package:suitcase_uld/algorithm/branch_and_bound/define_table.dart';
import 'package:suitcase_uld/algorithm/branch_and_bound/input.dart';

void main() {
  // Initialize tables (from defineTable)
  initTables();

  // Number of bags and items
  const int bagCount = 3;
  const int itemCount = 8;

  // Bag dimensions and capacities
  List<int> bagx = [5, 10, 30];
  List<int> bagy = [3, 10, 14];
  List<int> bagz = [3, 10, 14];
  List<int> bagCap = [40, 40, 45];

  // Initialize bags
  List<Bag> bags = List.generate(bagCount, (i) {
    Bag bag = Bag();
    bag.setAttribute(bagx[i], bagy[i], bagz[i], bagCap[i]);
    bag.initMap();
    return bag;
  });

  // Item dimensions and weights
  List<int> xinputs = [1, 2, 3, 2, 5, 7, 3, 2];
  List<int> yinputs = [2, 2, 3, 3, 4, 3, 3, 2];
  List<int> zinputs = [2, 2, 3, 3, 4, 3, 3, 2];
  List<int> weightInputs = [1, 2, 3, 2, 1, 2, 3, 1];

  // Initialize items
  List<Item> items = List.generate(itemCount, (i) {
    return Item(
        x: xinputs[i], y: yinputs[i], z: zinputs[i], weight: weightInputs[i]);
  });

  // Calculate the minimum number of bags needed
  int result = getMinBagCount(items, bags, itemCount);

  // Display the result
  print("Minimum number of bags required: $result");
}
