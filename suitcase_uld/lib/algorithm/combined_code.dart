// Contents of branch_and_bound.dart
// Dart translation of branchAndBound.h and branchAndBound.cpp
class Node {
  int item = -1;
  List<Bag>? bagState;
  List<bool>? bagUsage;
  int currentBagUsage = 0;
  int bagCount = 0;

  Node();

  // Initializes bag states
  void initializeBagState(List<Bag> listOfBags) {
    bagCount = listOfBags.length;
    bagState = List.from(listOfBags);
    bagUsage = List.filled(bagCount, false);
  }

  int getUsedBagVolume() {
    int sum = 0;
    for (int i = 0; i < bagCount; i++) {
      if (bagUsage![i]) {
        sum += bagState![i].getVolume();
      }
    }
    return sum;
  }
}

class Queue {
  List<Node> buffer;
  int capacity;
  int size = 0;
  int front = 0;
  int rear = -1;
  int bagCount;

  Queue(this.capacity, this.bagCount) : buffer = List.filled(capacity, Node());

  void push(Node node) {
    if (size == capacity) throw Exception("Queue full!");
    size++;
    rear = (rear + 1) % capacity;
    buffer[rear] = node;
  }

  Node pop() {
    if (size == 0) throw Exception("Queue empty so cannot delete!");
    size--;
    Node node = buffer[front];
    front = (front + 1) % capacity;
    return node;
  }

  bool isEmpty() => size == 0;
}

// Bounding function
int bound(Node node) => node.currentBagUsage;

// Main function to get minimum bag count
int getMinBagCount(List<Item> items, List<Bag> bags, int itemCount) {
  final queue = Queue(10000, bags.length);
  Node popped, toPush = Node();

  // Current worst case minimum bag usage
  int currentMinBagUsage = itemCount;
  int smallestBagVolume = double.maxFinite.toInt();

  // Dummy node
  popped = Node();
  popped.item = -1;
  popped.initializeBagState(bags);
  queue.push(popped);

  while (!queue.isEmpty()) {
    popped = queue.pop();

    if (popped.item != itemCount - 1) {
      for (int i = 0; i < bags.length; i++) {
        toPush = Node();
        toPush.item = popped.item + 1;
        toPush.initializeBagState(bags);

        bool wasPutIn = toPush.bagState![i].tryItem(items[toPush.item]);

        if (wasPutIn) {
          toPush.bagUsage![i] = true;

          if (toPush.bagState![i].getItemCount() != 1) {
            toPush.currentBagUsage = popped.currentBagUsage - 1;
          }

          if (toPush.currentBagUsage + (itemCount - 1 - toPush.item) <
              currentMinBagUsage) {
            currentMinBagUsage =
                toPush.currentBagUsage + (itemCount - 1 - toPush.item);
          }

          if (bound(toPush) <= currentMinBagUsage) {
            queue.push(toPush);
          }

          if (toPush.getUsedBagVolume() < smallestBagVolume &&
              (toPush.item == itemCount - 1)) {
            smallestBagVolume = toPush.getUsedBagVolume();
          }
        }
      }
    } else {
      if (popped.getUsedBagVolume() == smallestBagVolume) {
        // Increment outcome and print details
        int outcome = 0;
        outcome++;

        print("Outcome $outcome:");

        for (int i = 0; i < bags.length; ++i) {
          print("Bag ${i + 1}:");
          popped.bagState![i].printBagMap();
          popped.bagState![i].printItemInfo();
        }
      }
    }
  }

  return currentMinBagUsage;
}

// Contents of define_table.dart
// Dart translation of defineTable.cpp

List<int> bitTable = [0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe];
List<int> valueToKey =
    List.filled(256, 8); // default to 8 as the uninitialized value

void initTables() {
  valueToKey[255] = 0; // 1111 1111
  valueToKey[254] = 1; // 1111 1110
  valueToKey[252] = 2; // 1111 1100
  valueToKey[248] = 3; // 1111 1000
  valueToKey[240] = 4; // 1111 0000
  valueToKey[224] = 5; // 1110 0000
  valueToKey[192] = 6; // 1100 0000
  valueToKey[128] = 7; // 1000 0000
  valueToKey[0] = 8; // 0000 0000
}

List<List<int>> shiftMap8bit = [
  [
    4278190080,
    2139095040,
    1069547520,
    534773760,
    267386880,
    133693440,
    66846720,
    33423360
  ],
  [
    4261412864,
    2130706432,
    1065353216,
    532676608,
    266338304,
    133169152,
    66584576,
    33292288
  ],
  [
    4227858432,
    2113929216,
    1056964608,
    528482304,
    264241152,
    132120576,
    66060288,
    33030144
  ],
  [
    4160749568,
    2080374784,
    1040187392,
    520093696,
    260046848,
    130023424,
    65011712,
    32505856
  ],
  [
    4026531840,
    2013265920,
    1006632960,
    503316480,
    251658240,
    125829120,
    62914560,
    31457280
  ],
  [
    3758096384,
    1879048192,
    939524096,
    469762048,
    234881024,
    117440512,
    58720256,
    29360128
  ],
  [
    3221225472,
    1610612736,
    805306368,
    402653184,
    201326592,
    100663296,
    50331648,
    25165824
  ]
];

List<List<int>> shiftMapByte = [
  [
    4294967040,
    2147483520,
    1073741760,
    536870880,
    268435440,
    134217720,
    67108860,
    33554430
  ],
  [
    4294966784,
    2147483392,
    1073741696,
    536870848,
    268435424,
    134217712,
    67108856,
    33554428
  ],
  [
    4294966272,
    2147483136,
    1073741568,
    536870784,
    268435392,
    134217696,
    67108848,
    33554424
  ],
  [
    4294965248,
    2147482624,
    1073741312,
    536870656,
    268435328,
    134217664,
    67108832,
    33554416
  ],
  [
    4294963200,
    2147481600,
    1073740800,
    536870400,
    268435200,
    134217600,
    67108800,
    33554400
  ],
  [
    4294959104,
    2147479552,
    1073739776,
    536869888,
    268434944,
    134217472,
    67108736,
    33554368
  ],
  [
    4294950912,
    2147475456,
    1073737728,
    536868864,
    268434432,
    134217216,
    67108608,
    33554304
  ],
  [
    4294934528,
    2147467264,
    1073733632,
    536866816,
    268433408,
    134216704,
    67108352,
    33554176
  ],
  [
    4294901760,
    2147450880,
    1073725440,
    536862720,
    268431360,
    134215680,
    67107840,
    33553920
  ]
];

// Contents of input.dart
// Dart translation of input.h

class Item {
  int x, y, z, weight;

  Item({this.x = 0, this.y = 0, this.z = 0, this.weight = 0});

  // Methods like constructors or operators can be added here if necessary
}

class ItemList {
  Item? item;
  ItemList? nextItemOnList;

  ItemList({this.item, this.nextItemOnList});

  // Add an item to the list
  void addItemToList(Item itemToInclude) {
    nextItemOnList = ItemList(item: itemToInclude);
  }

  // Deletes item and all items after it in the list
  void deleteList() {
    nextItemOnList = null;
  }
}

class Bag {
  int x = 0, y = 0, z = 0, maxCapacity = 0;
  int itemCount = 0, itemWeightSum = 0;
  List<int>? map;
  ItemList? firstItemPtr;
  ItemList? lastItemPtr;

  Bag();

  int getVolume() => x * y * z;

  int getItemCount() => itemCount;

  void setAttribute(int x, int y, int z, int maxCapacity) {
    x = x;
    y = y;
    z = z;
    maxCapacity = maxCapacity;
  }

  bool tryItem(Item itemToCheck) {
    // Add logic for item check if necessary
    return false;
  }

  void putIn(Item itemToInclude, int bitShifts, List<int> itemMap) {
    // Add logic for putting item in
  }

  void addItemToBag(Item itemToAdd) {
    itemCount++;
    itemWeightSum += itemToAdd.weight;
    if (firstItemPtr == null) {
      firstItemPtr = ItemList(item: itemToAdd);
      lastItemPtr = firstItemPtr;
    } else {
      lastItemPtr?.nextItemOnList = ItemList(item: itemToAdd);
      lastItemPtr = lastItemPtr?.nextItemOnList;
    }
  }

  void initMap() {
    map = List.filled((x * y * z + 7) ~/ 8, 0);
  }

  void printBagMap() {
    print("Bag map data..."); // 실제 Bag 맵 데이터로 교체
  }

  void printItemInfo() {
    print("Item info data..."); // 실제 Item 정보를 여기로 출력
  }
}

// Contents of source.dart
// Dart translation of source.cpp

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
