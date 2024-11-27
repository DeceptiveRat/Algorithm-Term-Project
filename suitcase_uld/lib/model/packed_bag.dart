class PackedBag {
  List<List<List<int>>> space;
  int usedVolume = 0;
  double usageRate = 0.0;

  PackedBag(int width, int height, int depth)
      : space = List.generate(
            width,
            (_) =>
                List.generate(height, (_) => List.generate(depth, (_) => 0)));

  void updateUsageRate(int totalVolume) {
    usageRate = (usedVolume * 100.0) / totalVolume;
  }
}
