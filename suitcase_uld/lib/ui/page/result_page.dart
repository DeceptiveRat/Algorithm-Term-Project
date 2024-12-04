import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/algorithm/branch_and_bound.dart/branch_and_bound.dart';
import 'dart:math';

import 'package:suitcase_uld/algorithm/greedy_dp/source.dart';
import 'package:suitcase_uld/controller/view_controller.dart';

class ResultPage extends StatefulWidget {
  const ResultPage({super.key});

  static const String url = '/resultPage';

  @override
  State<ResultPage> createState() => _ResultPageState();
}

class _ResultPageState extends State<ResultPage> {
  final ViewController viewController = Get.find();
  final Source greedyDPController = Get.find();
  final BranchAndBound branchAndBound = Get.find();
  final Random random = Random();

  // Generate a random color for each item number
  final Map<int, Color> colorMap = {};

  Color getColor(int number) {
    if (!colorMap.containsKey(number)) {
      colorMap[number] = Color.fromARGB(
        255,
        random.nextInt(256),
        random.nextInt(256),
        random.nextInt(256),
      );
    }
    return colorMap[number]!;
  }

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
              // 최소 개수 섹션
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
                          child: Obx(() {
                            if (greedyDPController
                                .resultMinimumNumber.isEmpty) {
                              return const Center(child: Text("결과를 생성하세요."));
                            }
                            return ListView.builder(
                              itemCount:
                                  greedyDPController.resultMinimumNumber.length,
                              itemBuilder: (context, index) {
                                final bagInfo = greedyDPController
                                    .resultMinimumNumber[index];
                                return ListTile(
                                  title: Text("Bag: ${bagInfo['name']}"),
                                  subtitle: Text(
                                      "Usage Rate: ${bagInfo['usageRate']}%"),
                                  onTap: () {
                                    Navigator.push(
                                      context,
                                      MaterialPageRoute(
                                        builder: (context) => BagDetailPage(
                                          bagInfo: bagInfo,
                                          getColor: getColor,
                                        ),
                                      ),
                                    );
                                  },
                                );
                              },
                            );
                          }),
                        ),
                      ),
                    ],
                  ),
                ),
              ),
              const Divider(),
              // 최소 용량 섹션
              Expanded(
                flex: 1,
                child: Container(
                  padding: const EdgeInsets.all(8.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      const Text('최소 용량 가방', style: TextStyle(fontSize: 30)),
                      Expanded(
                        child: Container(
                          width: double.infinity,
                          color: Colors.grey[200],
                          child: Obx(() {
                            if (greedyDPController.resultMinimumSize.isEmpty) {
                              return const Center(child: Text("결과를 생성하세요."));
                            }
                            return ListView.builder(
                              itemCount:
                                  greedyDPController.resultMinimumSize.length,
                              itemBuilder: (context, index) {
                                final bagInfo =
                                    greedyDPController.resultMinimumSize[index];
                                return ListTile(
                                  title: Text("Bag: ${bagInfo['name']}"),
                                  subtitle: Text(
                                      "Usage Rate: ${bagInfo['usageRate']}%"),
                                  onTap: () {
                                    Navigator.push(
                                      context,
                                      MaterialPageRoute(
                                        builder: (context) => BagDetailPage(
                                          bagInfo: bagInfo,
                                          getColor: getColor,
                                        ),
                                      ),
                                    );
                                  },
                                );
                              },
                            );
                          }),
                        ),
                      ),
                    ],
                  ),
                ),
              ),
              // const Divider(),
              // // 최소 용량 섹션
              // Expanded(
              //   flex: 1,
              //   child: Container(
              //     padding: const EdgeInsets.all(8.0),
              //     child: Column(
              //       crossAxisAlignment: CrossAxisAlignment.start,
              //       children: [
              //         const Text('최적해 반환 결과', style: TextStyle(fontSize: 30)),
              //         Expanded(
              //           child: Container(
              //             width: double.infinity,
              //             color: Colors.grey[200],
              //             child: Obx(() {
              //               if (branchAndBound.result.isEmpty) {
              //                 return const Center(child: Text("결과를 생성하세요."));
              //               }
              //               return ListView.builder(
              //                 itemCount: branchAndBound.result.length,
              //                 itemBuilder: (context, index) {
              //                   final bagInfo = branchAndBound.result[index];
              //                   return ListTile(
              //                     title: Text("Bag: ${bagInfo['name']}"),
              //                     subtitle: Text(
              //                         "Usage Rate: ${bagInfo['usageRate']}%"),
              //                     onTap: () {
              //                       Navigator.push(
              //                         context,
              //                         MaterialPageRoute(
              //                           builder: (context) => BagDetailPage(
              //                             bagInfo: bagInfo,
              //                             getColor: getColor,
              //                           ),
              //                         ),
              //                       );
              //                     },
              //                   );
              //                 },
              //               );
              //             }),
              //           ),
              //         ),
              //       ],
              //     ),
              //   ),
              // ),
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

class BagDetailPage extends StatelessWidget {
  final Map<String, dynamic> bagInfo;
  final Color Function(int) getColor;

  const BagDetailPage(
      {required this.bagInfo, required this.getColor, super.key});

  @override
  Widget build(BuildContext context) {
    final levels = bagInfo['levels'] as List<List<List<int>>>;

    // 아이템 번호를 추출
    final Set<int> itemNumbers = {};
    for (var level in levels) {
      for (var row in level) {
        itemNumbers.addAll(row.where((number) => number != 0));
      }
    }
    final sortedItemNumbers = itemNumbers.toList()..sort();

    return Scaffold(
      appBar: AppBar(
        title: Text("Bag: ${bagInfo['name']}"),
      ),
      body: Column(
        children: [
          // 아이템 번호와 색상 매핑 리스트
          Padding(
            padding: const EdgeInsets.all(8.0),
            child: SizedBox(
              height: 50, // 리스트 높이 설정
              child: ListView.builder(
                scrollDirection: Axis.horizontal,
                itemCount: sortedItemNumbers.length,
                itemBuilder: (context, index) {
                  final itemNumber = sortedItemNumbers[index];
                  final color = getColor(itemNumber);
                  return Row(
                    children: [
                      Container(
                        width: 30,
                        height: 30,
                        color: color,
                        margin: const EdgeInsets.only(right: 8.0),
                      ),
                      Text(
                        "Item $itemNumber",
                        style: const TextStyle(fontSize: 16),
                      ),
                      const SizedBox(width: 16),
                    ],
                  );
                },
              ),
            ),
          ),
          Expanded(
            child: ListView.builder(
              itemCount: levels.length,
              itemBuilder: (context, depthIndex) {
                final level = levels[depthIndex];
                return Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Text(
                        "Depth ${depthIndex + 1}cm",
                        style: const TextStyle(fontSize: 20),
                      ),
                    ),
                    GridView.builder(
                      shrinkWrap: true,
                      physics: const NeverScrollableScrollPhysics(),
                      gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
                        crossAxisCount: level.length, // 가방의 너비에 맞게 열 수 설정
                      ),
                      itemCount: level.length * level[0].length,
                      itemBuilder: (context, index) {
                        final x = index % level.length;
                        final y = index ~/ level.length;
                        final number = level[x][y];
                        return Container(
                          margin: const EdgeInsets.all(2.0),
                          color: number == 0 ? Colors.grey : getColor(number),
                        );
                      },
                    ),
                  ],
                );
              },
            ),
          ),
        ],
      ),
    );
  }
}
