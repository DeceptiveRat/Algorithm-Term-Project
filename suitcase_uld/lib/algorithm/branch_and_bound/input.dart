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
