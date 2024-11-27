import 'package:get/get.dart';

class ScreenSize extends GetxService {
  static double get getWidth => GetPlatform.isMobile ? Get.width : 500;
  static double get getHeight => GetPlatform.isMobile ? Get.height : 1000;
}
