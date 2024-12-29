#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include <opencv2/opencv.hpp>
#include <iostream>

// 鼠标回调函数
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) { // 左键单击事件
        cv::Mat& img = *(cv::Mat*)userdata;
        // 在点击位置绘制一个红点
        cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
        // 显示更新后的图像
        cv::imshow("Image", img);
        // 输出相对图像的坐标
        std::cout << "Clicked at (" << x << ", " << y << ")" << std::endl;
    }
}

int main() {
    // 读取图像
    cv::Mat img = cv::imread("../resources/cards.jpg");
    // 创建窗口并显示图像
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", img);
    // 设置鼠标回调函数
    cv::setMouseCallback("Image", onMouse, &img);
    // 等待用户按下键盘退出
    cv::waitKey(0);
    return 0;
}


// // 鼠标回调函数
// void onMouse(int event, int x, int y, int flags, void *userdata) {
//   if (event == cv::EVENT_LBUTTONDOWN) { // 左键单击事件
//     // 获取图像和点集
//     auto *data = (std::pair<cv::Mat, std::vector<cv::Point>> *)userdata;
//     cv::Mat &img = data->first;
//     std::vector<cv::Point> &points = data->second;

//     // 记录点并在图像上标注
//     points.emplace_back(x, y);
//     cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
//     cv::imshow("Image", img);

//     // 输出点击的坐标
//     std::cout << "Clicked at (" << x << ", " << y << ")" << std::endl;
//   }
// }

// // 重绘图像，清除所有标注并重新绘制
// void redrawImage(cv::Mat &baseImg, cv::Mat &displayImg,
//                  const std::vector<cv::Point> &points) {
//   // 复制原始图像
//   displayImg = baseImg.clone();

//   // 重新绘制所有点
//   for (const auto &point : points) {
//     cv::circle(displayImg, point, 5, cv::Scalar(0, 0, 255), -1);
//   }

//   // 更新显示
//   cv::imshow("Image", displayImg);
// }

// int main() {
//   // 读取图像
//   cv::Mat baseImg = cv::imread("../resources/cards.jpg");

//   if (baseImg.empty()) {
//     std::cerr << "Failed to load image!" << std::endl;
//     return -1;
//   }

//   // 显示用的图像
//   cv::Mat displayImg = baseImg.clone();

//   // 用于存储标注点的容器
//   std::vector<cv::Point> points;

//   // 创建窗口并显示图像
//   cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
//   cv::imshow("Image", displayImg);

//   // 设置鼠标回调函数
//   std::pair<cv::Mat, std::vector<cv::Point>> data = {displayImg, points};
//   cv::setMouseCallback("Image", onMouse, &data);

//   // 主循环，监听键盘事件
//   while (true) {
//     int key = cv::waitKey(0);

//     if (key == 27) { // 按下 Esc 键退出
//       break;
//     } else if (key == 'z') { // 按下 Ctrl+Z 撤销
//       if (!data.second.empty()) {
//         // 移除最后一个点
//         data.second.pop_back();
//         std::cout << "Undo last point." << std::endl;

//         // 重绘图像
//         redrawImage(baseImg, displayImg, data.second);
//     } 
//     // else {
//     //     std::cout << "No points to undo." << std::endl;
//     //   }
//     }
//   }

//   return 0;
// }
