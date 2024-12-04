class Item {
  final String name;
  int width, height, depth, weight;
  int? number;
  bool isSelected;

  Item({
    required this.name,
    this.isSelected = false,
    required this.width,
    required this.height,
    required this.depth,
    required this.weight,
  });

  int get volume => width * height * depth;
}
