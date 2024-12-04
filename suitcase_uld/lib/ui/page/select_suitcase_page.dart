import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:get/get.dart';
import 'package:get/get_state_manager/get_state_manager.dart';
import 'package:suitcase_uld/controller/view_controller.dart';
import 'package:suitcase_uld/model/item.dart';
import 'package:suitcase_uld/ui/page/add_suitcase_page.dart';
import 'package:suitcase_uld/ui/page/select_uld_page.dart';

class SelectSuitCasePage extends StatefulWidget {
  const SelectSuitCasePage({super.key});

  static const String url = '/selectSuitCase';

  @override
  State<SelectSuitCasePage> createState() => _SelectSuitCasePageState();
}

class _SelectSuitCasePageState extends State<SelectSuitCasePage> {
  // final controller = ViewController();
  final ViewController viewController = Get.find();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("SelectSuitCase"),
        actions: [
          IconButton(
            onPressed: () {
              Get.toNamed('/addSuitCasePage');
            },
            icon: const Icon(Icons.add),
          )
        ],
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
                        const Text('선택한 수하물', style: TextStyle(fontSize: 30)),
                        Expanded(
                          child: Container(
                            color: Colors.grey[200],
                            child: ListView.builder(
                              itemCount:
                                  viewController.selectedSuitCaseList.length,
                              itemBuilder: (context, index) {
                                final item =
                                    viewController.selectedSuitCaseList[index];
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
                        const Text('전체 수하물', style: TextStyle(fontSize: 30)),
                        Expanded(
                          child: Container(
                            color: Colors.grey[200],
                            child: ListView.builder(
                              itemCount: viewController.suitCaseList.length,
                              itemBuilder: (context, index) {
                                final item = viewController.suitCaseList[index];
                                return CheckboxListTile(
                                  title: Text(item.name),
                                  subtitle: Text(
                                      "${item.width.toString()} * ${item.height.toString()} * ${item.depth.toString()}"),
                                  value: item.isSelected,
                                  onChanged: (isChecked) => viewController
                                      .onSuitCaseCheckedChange(item, isChecked),
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
                content: Text(viewController.selectedSuitCaseList
                    .map((e) => e.name)
                    .join(", ")),
                actions: [
                  TextButton(
                    onPressed: () {
                      Navigator.pop(context);
                      Get.to(const SelectULDPage());
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
