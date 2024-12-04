import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter/widgets.dart';
import 'package:get/get.dart';
import 'package:suitcase_uld/ui/page/add_direct_page.dart';
import 'package:suitcase_uld/util/screen_size.dart';

class AddSuitCasePage extends StatelessWidget {
  const AddSuitCasePage({super.key});

  static const String url = "/addSuitCasePage";

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Add SuitCase"),
      ),
      body: SafeArea(
        child: SingleChildScrollView(
          child: SizedBox(
            width: double.infinity,
            height: double.infinity,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                TextButton(
                  onPressed: () {
                    Get.toNamed('/addDirectPage');
                  },
                  child: SizedBox(
                    // decoration: BoxDecoration(
                    //   // border: Border.all(),
                    //   color: Colors.grey[200],
                    // ),
                    width: ScreenSize.getWidth / 4,
                    height: ScreenSize.getWidth / 4,
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Container(
                          child: Icon(
                            Icons.add_box_outlined,
                            size: ScreenSize.getWidth / 10,
                          ),
                        ),
                        const Text(
                          "직접\n추가하기",
                          textAlign: TextAlign.center,
                        ),
                      ],
                    ),
                  ),
                ),
                SizedBox(
                  width: ScreenSize.getWidth / 20,
                ),
                Container(
                  decoration: BoxDecoration(
                    // border: Border.all(),
                    color: Colors.grey[200],
                  ),
                  width: ScreenSize.getWidth / 4,
                  height: ScreenSize.getWidth / 4,
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Icon(
                        Icons.add_a_photo_outlined,
                        size: ScreenSize.getWidth / 10,
                      ),
                      const Text(
                        "사진 촬영하여\n추가하기",
                        textAlign: TextAlign.center,
                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
