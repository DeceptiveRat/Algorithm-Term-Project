import 'package:flutter/material.dart';
import 'package:suitcase_uld/ui/page/result_page.dart';

class TestScreen extends StatelessWidget {
  const TestScreen({super.key});

  static const String url = '/selectSuitCase';

  @override
  Widget build(BuildContext context) {
    return const ResultPage();
  }
}
