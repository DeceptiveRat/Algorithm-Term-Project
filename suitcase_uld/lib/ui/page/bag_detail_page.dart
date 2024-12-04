import 'dart:math';

import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/algorithm/greedy_dp/source.dart';

class BagDetailPage extends StatelessWidget {
  final int bagIndex; // 현재 선택된 가방의 인덱스
  final bool isMinimumNumber; // 최소 개수(true) 또는 최소 용량(false)

  const BagDetailPage({
    required this.bagIndex,
    required this.isMinimumNumber,
    super.key,
  });

  @override
  Widget build(BuildContext context) {
    final Source greedyDPController = Get.find();

    // result 리스트 선택
    final result = isMinimumNumber
        ? greedyDPController.resultMinimumNumber
        : greedyDPController.resultMinimumSize;

    // 선택한 가방 정보
    final bagInfo = result[bagIndex];

    // 모든 레벨 데이터 가져오기
    final levels = bagInfo['levels'] as List<List<List<int>>>;

    // 아이템 번호 추출
    final Set<int> itemNumbers = {};
    for (var level in levels) {
      for (var row in level) {
        itemNumbers.addAll(row.where((number) => number != 0));
      }
    }
    final sortedItemNumbers = itemNumbers.toList()..sort();

    // 랜덤 색상 매핑
    final Random random = Random();
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
