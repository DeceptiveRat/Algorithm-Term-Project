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
