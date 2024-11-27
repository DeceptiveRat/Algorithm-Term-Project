import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/algorithm/greedy_dp/minimum_source.dart';
import 'package:suitcase_uld/model/item.dart';

import '../../controller/view_controller.dart';

class SelectULDPage extends StatefulWidget {
  const SelectULDPage({super.key});

  static const String url = '/selectUld';

  @override
  State<SelectULDPage> createState() => _SelectULDPageState();
}

class _SelectULDPageState extends State<SelectULDPage> {
  final ViewController viewController = Get.find();
  final GreedyDPController2 greedyDPController = Get.find();
  // final controller = ViewController();
  // final greedyDPController = GreedyDPController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Select ULD"),
      ),
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Obx(() {
            return Column(
              children: [
                Expanded(
                  flex: 1,
                  child: Container(
                    padding: const EdgeInsets.all(8.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        const Text('선택한 ULD', style: TextStyle(fontSize: 30)),
                        Expanded(
                          child: Container(
                            color: Colors.grey[200],
                            child: ListView.builder(
                              itemCount: viewController.selectedUldList.length,
                              itemBuilder: (context, index) {
                                final item =
                                    viewController.selectedUldList[index];
                                return ListTile(
                                  title: Text(item.name),
                                  leading: const Icon(Icons.check),
                                );
                              },
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
                const Divider(),
                Expanded(
                  flex: 2,
                  child: Container(
                    padding: const EdgeInsets.all(8.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        const Text('전체 ULD', style: TextStyle(fontSize: 30)),
                        Expanded(
                          child: Container(
                            color: Colors.grey[200],
                            child: ListView.builder(
                              itemCount: viewController.uldList.length,
                              itemBuilder: (context, index) {
                                final item = viewController.uldList[index];
                                return CheckboxListTile(
                                  title: Text(item.name),
                                  value: item.isSelected,
                                  onChanged: (isChecked) => viewController
                                      .onUldCheckedChange(item, isChecked),
                                );
                              },
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
                const SizedBox(width: 16),
              ],
            );
          }),
        ),
      ),
      bottomNavigationBar: Padding(
        padding: const EdgeInsets.all(16.0),
        child: ElevatedButton(
          onPressed: () {
            // 확인 버튼 기능 구현
            showDialog(
              context: context,
              builder: (context) => AlertDialog(
                title: const Text("선택한 아이템"),
                content: Text(viewController.selectedUldList
                    .map((e) => e.name)
                    .join(", ")),
                actions: [
                  TextButton(
                    onPressed: () {
                      Navigator.pop(context);
                      greedyDPController.main(); // 결과를 생성하고 저장
                      Get.toNamed('/resultPage');
                    },
                    child: const Text("확인"),
                  ),
                ],
              ),
            );
          },
          child: const Text("확인"),
        ),
      ),
    );
  }
}
