class Item {
  int width;
  int length;
  int height;
  int weight;
  int number;

  Item({
    required this.width,
    required this.length,
    required this.height,
    required this.weight,
    required this.number,
  });

  int get volume => width * length * height;
}

class Bag {
  int width;
  int length;
  int height;
  String name;
  late int volume;

  Bag({
    required this.width,
    required this.length,
    required this.height,
    required this.name,
  }) {
    volume = width * length * height;
  }
}

class PackedBag {
  List<List<List<int>>> space;
  int usedVolume = 0;
  double usageRate = 0.0;

  PackedBag(int width, int length, int height)
      : space = List.generate(
          width,
          (_) => List.generate(length, (_) => List.filled(height, 0)),
        );

  void updateUsageRate(int bagVolume) {
    usageRate = (usedVolume * 100.0) / bagVolume;
  }
}

int compareItems(Item a, Item b) => b.volume - a.volume;
int compareBags(Bag a, Bag b) => a.volume - b.volume;

bool canPlace(PackedBag packedBag, int x, int y, int z, Item item, Bag bag) {
  if (x + item.width > bag.width ||
      y + item.length > bag.length ||
      z + item.height > bag.height) {
    return false;
  }

  if (z > 0) {
    bool hasSupport = false;
    for (int i = x; i < x + item.width; i++) {
      for (int j = y; j < y + item.length; j++) {
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
    for (int j = y; j < y + item.length; j++) {
      for (int k = z; k < z + item.height; k++) {
        if (packedBag.space[i][j][k] != 0) return false;
      }
    }
  }
  return true;
}

void placeItem(PackedBag packedBag, int x, int y, int z, Item item) {
  for (int i = x; i < x + item.width; i++) {
    for (int j = y; j < y + item.length; j++) {
      for (int k = z; k < z + item.height; k++) {
        packedBag.space[i][j][k] = item.number;
      }
    }
  }
  packedBag.usedVolume += item.volume;
}

void findMinimumBags(List<Item> items, List<Bag> bags) {
  bags.sort(compareBags);
  items.sort(compareItems);

  List<PackedBag> packedBags = List.generate(bags.length,
      (i) => PackedBag(bags[i].width, bags[i].length, bags[i].height));

  int currentBag = 0;

  for (Item item in items) {
    bool placed = false;
    while (!placed && currentBag < bags.length) {
      for (int z = 0; z < bags[currentBag].height && !placed; z++) {
        for (int x = 0; x < bags[currentBag].width && !placed; x++) {
          for (int y = 0; y < bags[currentBag].length && !placed; y++) {
            if (canPlace(
                packedBags[currentBag], x, y, z, item, bags[currentBag])) {
              placeItem(packedBags[currentBag], x, y, z, item);
              packedBags[currentBag].updateUsageRate(bags[currentBag].volume);
              placed = true;
            }
          }
        }
      }
      if (!placed) currentBag++;
    }
  }

  for (int b = 0; b <= currentBag; b++) {
    if (packedBags[b].usedVolume > 0) {
      print('\nBag ${bags[b].name}:');
      print('Usage rate: ${packedBags[b].usageRate.toStringAsFixed(1)}%');

      // Print layout for each height level
      for (int h = 0; h < bags[b].height; h++) {
        print("\nHeight ${h + 1}cm:");
        for (int x = 0; x < bags[b].width; x++) {
          String row = "";
          for (int y = 0; y < bags[b].length; y++) {
            row += packedBags[b].space[x][y][h] == 0
                ? "0"
                : "${packedBags[b].space[x][y][h]}";
          }
          print(row); // Print each row of the current height level
        }
      }
    }
  }
}

void findMinimumSize(List<Item> items, List<Bag> bags) {
  bags.sort((a, b) => b.volume - a.volume);
  items.sort(compareItems);

  PackedBag? bestPacking;
  int bestBagIndex = -1;
  double bestUsage = 0;

  for (int b = 0; b < bags.length; b++) {
    PackedBag currentPacking =
        PackedBag(bags[b].width, bags[b].length, bags[b].height);
    bool allItemsFit = true;

    for (Item item in items) {
      bool placed = false;
      for (int z = 0; z < bags[b].height && !placed; z++) {
        for (int x = 0; x < bags[b].width && !placed; x++) {
          for (int y = 0; y < bags[b].length && !placed; y++) {
            if (canPlace(currentPacking, x, y, z, item, bags[b])) {
              placeItem(currentPacking, x, y, z, item);
              placed = true;
            }
          }
        }
      }
      if (!placed) {
        allItemsFit = false;
        break;
      }
    }

    if (allItemsFit) {
      double usage = (currentPacking.usedVolume * 100.0) / bags[b].volume;
      if (usage > bestUsage) {
        bestUsage = usage;
        bestBagIndex = b;
        bestPacking = currentPacking;
      }
    }
  }

  if (bestBagIndex != -1) {
    print('\nBest bag found: ${bags[bestBagIndex].name}');
    print('Usage rate: ${bestUsage.toStringAsFixed(1)}%');

    // Print layout for each height level
    for (int h = 0; h < bags[bestBagIndex].height; h++) {
      print("\nHeight ${h + 1}cm:");
      for (int x = 0; x < bags[bestBagIndex].width; x++) {
        String row = "";
        for (int y = 0; y < bags[bestBagIndex].length; y++) {
          row += bestPacking!.space[x][y][h] == 0
              ? "0"
              : "${bestPacking.space[x][y][h]}";
        }
        print(row); // Print each row of the current height level
      }
    }
  } else {
    print('\nNo suitable bag found that can fit all items.');
  }
}

void main() {
  List<Item> items = [
    Item(width: 10, length: 20, height: 15, weight: 5, number: 1),
    Item(width: 15, length: 25, height: 10, weight: 3, number: 2),
    Item(width: 5, length: 8, height: 5, weight: 1, number: 3),
  ];

  List<Bag> bags = [
    Bag(width: 46, length: 27, height: 30, name: "AB bag"),
    Bag(width: 35, length: 21, height: 31, name: "BB bag"),
    Bag(width: 15, length: 13, height: 30, name: "Cross bag")
  ];

  print("\nSolution A (Minimum number of bags):");
  findMinimumBags(items, bags);

  print("\nSolution B (Minimum bag size):");
  findMinimumSize(items, bags);
}
