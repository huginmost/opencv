#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
const int MAX = 0x3f3f3f3f;

int main() {
  // 首先读取图像:将图像中的每一帧都读出来
  VideoCapture capture("../节目效果之监控幽默录像.flv");
  std::cout << capture.isOpened() << endl;
  Mat frame, last_frame;  // 获取上一帧图像
  capture.read(frame);

  // 预处理
  last_frame = Mat::zeros(frame.size(), frame.type());
  cvtColor(last_frame, last_frame, COLOR_BGR2GRAY);
  int cnt = 0;
  int MIN = MAX;

  // 目标:检测目标轮廓内的颜色变换,如果
  // 原本什么都没有后来出现了大面积的填充,那么就证明出现了一个白块
  // 因此需要对比,需要保存上一帧的图像与这一帧图像进行比较

  while (!frame.empty()) {
    // 转化为二值图像便于处理
    Mat gray, canny,
        sub;  // 分别为初步处理的灰度图像,Canny检测后的图像,作差后图像
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    // 检测边缘,获取方块的形状
    // 1.Canny边缘检测
    Canny(gray, canny, 50, 150);  // 灰度值图像进行Canny边缘检测
    // 2.findContours的写法
    std::vector<std::vector<Point>> contours;
    vector<Vec4i> hierarchy;
    cv::findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,
                     Point(0, 0));
    // 设置单通道的画布,用于描出基础的轮廓
    Mat drawing = Mat::zeros(canny.size(), CV_8UC1);
    // 设置单通道的画布,用于放置作差处理后的图像,初始均为0像素灰度值
    sub = Mat::zeros(canny.size(), CV_8UC1);

    // 3.drawContours写法
    for (int i = 0; i < contours.size(); i++) {
      Scalar color = Scalar(255, 255, 255);
      drawContours(drawing, contours, i, color, -1, 8, hierarchy, 0, Point());

      // 这两步用来调试的,找Area的阈值
      // int Area =
      // (int)(abs)(cv::contourArea(contours[i]));//如果是由暗转明，那么就一次
      // cout << Area << endl;
    }
    // 初步轮廓的显示,调试
    imshow("drawing", drawing);
    // 通过这一步过滤掉不需要的变化,只保留我们想要的那个变化

    // 4.遍历这一帧图像和上一帧图像
    // 如果说这一帧图像的像素点灰度值-上一帧图像的像素点灰度值
    // 是小于0的(原图像只有0或255)
    // 证明:这一帧为0,上一帧为255,是那种滑块从屏幕划走的情况,不要了直接跳过处理
    // 如果不是,那么就是滑块出现了,把作差处理画布对应像素值设置为255
    for (int i = 0; i < drawing.rows; i++) {
      for (int j = 0; j < drawing.cols; j++) {
        if (drawing.at<uchar>(i, j) - last_frame.at<uchar>(i, j) <= 0) {
          continue;
        }
        sub.at<uchar>(i, j) = drawing.at<uchar>(i, j);
      }
    }
    // 测试作差的处理的输出图像
    imshow("sub", sub);

    // 5.画作差图像的轮廓
    std::vector<std::vector<Point>> contours_sub;
    vector<Vec4i> hierarchy_sub;
    cv::findContours(sub, contours_sub, hierarchy_sub, RETR_TREE,
                     CHAIN_APPROX_SIMPLE, Point(0, 0));
    Mat drawing_sub = Mat::zeros(canny.size(), CV_8UC1);

    // 6.遍历作差图像轮廓,算轮廓面积,把之前用到的MIN值用上来筛选
    for (int i = 0; i < contours_sub.size(); i++) {
      Scalar color = Scalar(255, 255, 255);
      drawContours(drawing_sub, contours_sub, i, color, -1, 8, hierarchy, 0,
        Point());
      int Area = (int)abs(cv::contourArea(contours_sub[i]));
      if (Area >= 10000) {
        MIN = std::min(Area, MIN);
        // cout << Area<<endl;
        cnt++;
      }
    }
    // 观察者c
    char c = waitKey(10);

    // 设置迭代

    last_frame = drawing.clone();
    capture.read(frame);

    if (c == 27) {
      break;
    }
    if (c == '0') {
      waitKey(0);
    }
  }
  cout << MIN << endl << "检测到方块总数为:" << cnt;
  return 0;
}