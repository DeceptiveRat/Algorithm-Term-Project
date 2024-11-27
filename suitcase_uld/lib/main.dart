import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/algorithm/greedy_dp/source2.dart';
import 'package:suitcase_uld/controller/view_controller.dart';
import 'package:suitcase_uld/test_screen.dart';
import 'package:suitcase_uld/ui/page/main_page.dart';
import 'package:suitcase_uld/ui/page/result_page.dart';
import 'package:suitcase_uld/ui/page/select_suitcase_page.dart';
import 'package:suitcase_uld/ui/page/select_uld_page.dart';

import 'router.dart';

void main() {
  final ViewController viewController = Get.put(ViewController());
  final GreedyDPController2 greedyDPController = Get.put(GreedyDPController2());

  runApp(
    GetMaterialApp(
      initialRoute: TestScreen.url,
      theme: ThemeData(
        useMaterial3: true,
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.blue)
            .copyWith(background: Colors.white),
      ),
      getPages: CustomRouter.routes,
    ),
  );
}
