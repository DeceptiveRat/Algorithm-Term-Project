import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/algorithm/greedy_dp/minimum_source.dart';
import 'package:suitcase_uld/controller/view_controller.dart';
import 'package:suitcase_uld/ui/page/uld_layer.dart';

class ResultPage extends StatefulWidget {
  const ResultPage({super.key});

  static const String url = '/resultPage';

  @override
  State<ResultPage> createState() => _ResultPageState();
}

class _ResultPageState extends State<ResultPage> {
  final ViewController viewController = Get.find();
  final GreedyDPController2 greedyDPController = Get.find();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Result"),
      ),
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            children: [
              Expanded(
                flex: 1,
                child: Container(
                  padding: const EdgeInsets.all(8.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      const Text('최대 가방 크기', style: TextStyle(fontSize: 30)),
                      Expanded(
                        child: Container(
                          width: double.infinity,
                          color: Colors.grey[200],
                          child: Obx(() => Center(
                                child: TextButton(
                                    onPressed: () {
                                      Get.toNamed('/uldLayer');
                                    },
                                    child:
                                        Text(greedyDPController.uldInfo.value)),
                              )), // 결과를 Obx로 표시
                        ),
                      ),
                    ],
                  ),
                ),
              ),
              const Divider(),
              Expanded(
                flex: 1,
                child: Container(
                  padding: const EdgeInsets.all(8.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      const Text('최소 가방 개수', style: TextStyle(fontSize: 30)),
                      Expanded(
                        child: Container(
                          width: double.infinity,
                          color: Colors.grey[200],
                          child: Text(viewController.selectedSuitCaseList.length
                              .toString()),
                        ),
                      ),
                    ],
                  ),
                ),
              ),
              const SizedBox(width: 16),
            ],
          ),
        ),
      ),
      bottomNavigationBar: Padding(
        padding: const EdgeInsets.all(16.0),
        child: ElevatedButton(
          onPressed: () {
            greedyDPController.main(); // 결과를 생성하고 저장
          },
          child: const Text("확인"),
        ),
      ),
    );
  }
}
