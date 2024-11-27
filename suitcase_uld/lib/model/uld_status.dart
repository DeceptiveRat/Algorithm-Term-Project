class UldStatus {
  // 3D list to represent the bag space (0: empty space, positive integers: item number)
  List<List<List<int>>> space;
  int usedVolume; // Used volume
  double usageRate; // Usage rate (%)

  UldStatus({int width = 100, int length = 100, int height = 100})
      : usedVolume = 0,
        usageRate = 0.0,
        // Initialize the 3D space array with 0s
        space = List.generate(
            width, (_) => List.generate(length, (_) => List.filled(height, 0)));
}
