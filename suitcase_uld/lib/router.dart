import 'package:get/get.dart';
import 'package:suitcase_uld/test_screen.dart';
import 'package:suitcase_uld/ui/page/add_direct_page.dart';
import 'package:suitcase_uld/ui/page/add_suitcase_page.dart';
import 'package:suitcase_uld/ui/page/result_page.dart';
import 'package:suitcase_uld/ui/page/select_suitcase_page.dart';
import 'package:suitcase_uld/ui/page/select_uld_page.dart';
import 'package:suitcase_uld/ui/page/uld_layer.dart';

class CustomRouter {
  static final routes = [
    GetPage(name: SelectULDPage.url, page: () => const SelectULDPage()),
    GetPage(
        name: SelectSuitCasePage.url, page: () => const SelectSuitCasePage()),
    GetPage(name: ResultPage.url, page: () => const ResultPage()),
    // GetPage(name: TestScreen.url, page: () => const TestScreen()),
    GetPage(name: AddSuitCasePage.url, page: () => const AddSuitCasePage()),
    // GetPage(name: UldLayer.url, page: () => const UldLayer()),
    GetPage(name: AddDirectPage.url, page: () => AddDirectPage()),
  ];
}
