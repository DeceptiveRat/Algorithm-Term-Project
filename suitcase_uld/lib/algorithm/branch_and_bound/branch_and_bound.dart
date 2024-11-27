// Dart translation of branchAndBound.h and branchAndBound.cpp

import 'package:suitcase_uld/algorithm/branch_and_bound/input.dart';

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
