// import 'package:flutter/material.dart';
// import 'package:get/get.dart';
// import 'package:suitcase_uld/algorithm/greedy_dp/minimum_source.dart';
// import 'package:suitcase_uld/algorithm/greedy_dp/source.dart';

// class UldLayer extends StatefulWidget {
//   const UldLayer({super.key});

//   static const String url = '/uldLayer';

//   @override
//   State<UldLayer> createState() => _UldLayerState();
// }

// class _UldLayerState extends State<UldLayer> {
//   final Source greedyDPController = Get.find();

//   // 색상을 숫자와 매핑
//   final Map<int, Color> colorMap = {
//     0: Colors.grey, // 0은 회색
//     1: Colors.red, // 1은 빨간색
//     2: Colors.orange, // 2는 주황색
//     3: Colors.blue, // 3은 파란색
//     4: Colors.green, // 4는 초록색
//     5: Colors.purple,
//     6: Colors.yellow,
//     // 필요에 따라 추가 색상을 정의
//   };

//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: const Text("ULD Layer"),
//       ),
//       body: SafeArea(
//         child: Obx(() {
//           // Depth 구역을 슬라이싱하여 제거한 후 숫자 데이터만 추출
//           List<String> layers = greedyDPController.result.value
//               .split("\nDepth") // Depth 구역으로 나누기
//               .map((section) {
//                 // Depth부터 :까지 슬라이싱하여 제거
//                 int colonIndex = section.indexOf(':');
//                 if (colonIndex != -1) {
//                   section = section.substring(colonIndex + 1);
//                 }
//                 return section
//                     .replaceAll(RegExp(r'[^\d\n]'), '')
//                     .trim(); // 숫자와 줄바꿈만 남기고 나머지 제거
//               })
//               .where((section) =>
//                   section.isNotEmpty &&
//                   section.contains(RegExp(r'[1-9]'))) // 빈 섹션과 숫자 없는 섹션 제거
//               .toList();

//           return ListView.builder(
//             itemCount: layers.length,
//             itemBuilder: (context, layerIndex) {
//               // 각 Depth 구역의 데이터를 가져와서 줄 단위로 나누기
//               String layerData = layers[layerIndex];
//               List<String> rows = layerData.split("\n");

//               return Column(
//                 crossAxisAlignment: CrossAxisAlignment.start,
//                 children: [
//                   Text("Depth ${layerIndex + 1}cm", // Depth 제목 표시
//                       style: const TextStyle(
//                           fontSize: 18, fontWeight: FontWeight.bold)),
//                   const SizedBox(height: 10),
//                   SingleChildScrollView(
//                     scrollDirection: Axis.horizontal,
//                     child: Container(
//                       decoration: BoxDecoration(border: Border.all()),
//                       child: Column(
//                         crossAxisAlignment: CrossAxisAlignment.start,
//                         children: rows.map((row) {
//                           List<int> cells = row.split("").map((char) {
//                             // 숫자가 아니면 0으로 간주하여 처리
//                             return int.tryParse(char) ?? 0;
//                           }).toList();

//                           return Row(
//                             mainAxisAlignment: MainAxisAlignment.center,
//                             children: cells.map((cell) {
//                               return Container(
//                                 width: 30,
//                                 height: 30,
//                                 color: colorMap[cell] ?? Colors.grey, // 색상을 매핑
//                                 margin: const EdgeInsets.all(2),
//                               );
//                             }).toList(),
//                           );
//                         }).toList(),
//                       ),
//                     ),
//                   ),
//                   const SizedBox(height: 20), // Depth 구역 사이에 줄바꿈 추가
//                 ],
//               );
//             },
//           );
//         }),
//       ),
//     );
//   }
// }
