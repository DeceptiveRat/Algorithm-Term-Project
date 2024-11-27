import 'package:get/get.dart';
import 'package:suitcase_uld/model/item.dart';

class ViewController extends GetxController {
  final RxList<Item> _suitCaseList = <Item>[
    Item(name: "Item1", width: 3, height: 4, depth: 5, weight: 6),
    Item(name: "Item2", width: 2, height: 4, depth: 5, weight: 15),
    Item(name: "Item3", width: 3, height: 2, depth: 5, weight: 15),
    Item(name: "Item4", width: 4, height: 3, depth: 1, weight: 15),
    Item(name: "Item5", width: 2, height: 3, depth: 2, weight: 15),
    Item(name: "Item6", width: 2, height: 3, depth: 2, weight: 15),
  ].obs;
  final RxList<Item> _selectedSuitCaseList = <Item>[].obs;
  final RxList<Item> _uldList = <Item>[
    Item(name: "Container1", width: 10, height: 15, depth: 10, weight: 15),
    Item(name: "Container2", width: 20, height: 13, depth: 10, weight: 15),
    Item(name: "Container3", width: 30, height: 30, depth: 10, weight: 15),
    Item(name: "Container4", width: 10, height: 3, depth: 10, weight: 15),
  ].obs;
  final RxList<Item> _selectedUldList = <Item>[].obs;

  List<Item> get suitCaseList => _suitCaseList;
  List<Item> get selectedSuitCaseList => _selectedSuitCaseList;
  List<Item> get uldList => _uldList;
  List<Item> get selectedUldList => _selectedUldList;

  void onSuitCaseCheckedChange(Item item, bool? isChecked) {
    item.isSelected = isChecked ?? false;
    if (item.isSelected) {
      _selectedSuitCaseList.add(item);
      print(_selectedSuitCaseList.length);
    } else {
      _selectedSuitCaseList.remove(item);
    }
  }

  void onUldCheckedChange(Item item, bool? isChecked) {
    item.isSelected = isChecked ?? false;
    if (item.isSelected) {
      _selectedUldList.add(item);
      print(_selectedUldList.length);
    } else {
      _selectedUldList.remove(item);
    }
  }

  void addSuitCaseList(
      String name, int width, int height, int depth, int weight) {
    final newItem = Item(
      name: name,
      width: width,
      height: height,
      depth: depth,
      weight: weight,
    );
    _suitCaseList.add(newItem);
  }
}
