import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/model/item.dart';

import '../../controller/view_controller.dart';

class DevidedGroup extends StatefulWidget {
  const DevidedGroup({super.key});

  // static const String url = '/devidedGroup';

  @override
  State<DevidedGroup> createState() => _DevidedGroupState();
}

class _DevidedGroupState extends State<DevidedGroup> {
  final controller = ViewController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Title"),
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
                        const Text('selected group',
                            style: TextStyle(fontSize: 30)),
                        Expanded(
                          child: Container(
                            color: Colors.grey[200],
                            child: ListView.builder(
                              itemCount: controller.selectedUldList.length,
                              itemBuilder: (context, index) {
                                final item = controller.selectedUldList[index];
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
                        const Text('entire group',
                            style: TextStyle(fontSize: 30)),
                        Expanded(
                          child: Container(
                            color: Colors.grey[200],
                            child: ListView.builder(
                              itemCount: controller.uldList.length,
                              itemBuilder: (context, index) {
                                final item = controller.uldList[index];
                                return CheckboxListTile(
                                  title: Text(item.name),
                                  value: item.isSelected,
                                  onChanged: (isChecked) => controller
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
                title: const Text("selected item"),
                content: Text(
                    controller.selectedUldList.map((e) => e.name).join(", ")),
                actions: [
                  TextButton(
                    onPressed: () => Navigator.pop(context),
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
