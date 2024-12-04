import 'package:get/get.dart';
import 'package:suitcase_uld/model/bag.dart';
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

  final RxList<Bag> _uldList = <Bag>[
    Bag(width: 10, height: 10, depth: 10, name: "Bag 1"),
    Bag(width: 3, height: 7, depth: 5, name: "Bag 2"),
    Bag(width: 5, height: 5, depth: 3, name: "Bag 3"),
    Bag(width: 8, height: 2, depth: 7, name: "Bag 4"),
    Bag(width: 5, height: 5, depth: 5, name: "Bag 5"),
  ].obs;
  final RxList<Bag> _selectedUldList = <Bag>[].obs;

  List<Item> get suitCaseList => _suitCaseList;
  List<Item> get selectedSuitCaseList => _selectedSuitCaseList;
  List<Bag> get uldList => _uldList;
  List<Bag> get selectedUldList => _selectedUldList;

  void onSuitCaseCheckedChange(Item item, bool? isChecked) {
    item.isSelected = isChecked ?? false;
    if (item.isSelected) {
      _selectedSuitCaseList.add(item);
      print(_selectedSuitCaseList.length);
    } else {
      _selectedSuitCaseList.remove(item);
    }
  }

  void onUldCheckedChange(Bag bag, bool? isChecked) {
    bag.isSelected = isChecked ?? false;
    if (bag.isSelected) {
      _selectedUldList.add(bag);
      print(_selectedUldList.length);
    } else {
      _selectedUldList.remove(bag);
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
