class Bag {
  int width;
  int height;
  int depth;
  String name;
  late int volume;
  bool isSelected;

  Bag({
    required this.width,
    required this.height,
    required this.depth,
    required this.name,
    this.isSelected = false,
  }) {
    volume = width * height * depth;
  }
}
