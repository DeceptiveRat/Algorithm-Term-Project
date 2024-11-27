import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:get/get.dart';

import '../../controller/view_controller.dart';

class AddDirectPage extends StatelessWidget {
  AddDirectPage({super.key});

  static const String url = "/addDirectPage";

  final TextEditingController _nameInputController = TextEditingController();
  final TextEditingController _widthInputController = TextEditingController();
  final TextEditingController _heightInputController = TextEditingController();
  final TextEditingController _depthInputController = TextEditingController();
  final TextEditingController _weightInputController = TextEditingController();

  final ViewController viewController = Get.find<ViewController>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Add Suitcase"),
      ),
      body: SafeArea(
          child: Container(
        padding: const EdgeInsets.all(8.0),
        child: Column(
          children: [
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: TextField(
                controller: _nameInputController,
                decoration: const InputDecoration(
                  labelText: "Name",
                  border: OutlineInputBorder(),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: TextField(
                controller: _widthInputController,
                decoration: const InputDecoration(
                  labelText: "Width",
                  border: OutlineInputBorder(),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: TextField(
                controller: _heightInputController,
                decoration: const InputDecoration(
                  labelText: "Height",
                  border: OutlineInputBorder(),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: TextField(
                controller: _depthInputController,
                decoration: const InputDecoration(
                  labelText: "Depth",
                  border: OutlineInputBorder(),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: TextField(
                controller: _weightInputController,
                decoration: const InputDecoration(
                  labelText: "Weight",
                  border: OutlineInputBorder(),
                ),
              ),
            ),
            TextButton(
              onPressed: () {
                final String name = _nameInputController.text;
                final int width = int.tryParse(_widthInputController.text) ?? 0;
                final int height =
                    int.tryParse(_heightInputController.text) ?? 0;
                final int depth = int.tryParse(_depthInputController.text) ?? 0;
                final int weight =
                    int.tryParse(_weightInputController.text) ?? 0;

                viewController.addSuitCaseList(
                    name, width, height, depth, weight);

                showDialog(
                  context: context,
                  builder: (context) => AlertDialog(
                    title: const Text("항목이 추가되었습니다."),
                    content: Text(viewController.selectedSuitCaseList
                        .map((e) => e.name)
                        .join(", ")),
                    actions: [
                      TextButton(
                        onPressed: () {
                          Navigator.pop(context);
                        },
                        child: const Text("확인"),
                      ),
                    ],
                  ),
                );

                // Clear the text fields after adding
                _nameInputController.clear();
                _widthInputController.clear();
                _heightInputController.clear();
                _depthInputController.clear();
                _weightInputController.clear();
              },
              child: const Text("OK"),
            ),
          ],
        ),
      )),
    );
  }
}
