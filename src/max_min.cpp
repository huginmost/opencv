#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define outputLine() std::cout << "---------------------" << std::endl

int main(int argc, char const *argv[]) {
  // 对两张彩色图像进行比较运算
  Mat img0 = imread(
      "E:/graduate/learn/OpenCV/《OpenCV 4快速入门》数据集/data/lena.png");
  Mat img1 = imread(
      "E:/graduate/learn/OpenCV/《OpenCV 4快速入门》数据集/data/noobcv.jpg");

  if (img0.empty() || img1.empty()) {
    cout << "请确认图像文件名称是否正确" << endl;
    return -1;
  }
  Mat comMin, comMax;
  max(img0, img1, comMax);
  min(img0, img1, comMin);
  imshow("comMin", comMin);
  imshow("comMax", comMax);

  // 与掩模进行比较运算
  Mat src1 = Mat::zeros(Size(512, 512), CV_8UC3); // 生成一个512*512的0矩阵
  Rect rect(100, 100, 300, 300); // 创建一个坐标点(100,100)开始的300*300的矩形
  src1(rect) = Scalar(
      255, 255,
      255); // 生成一个低通300*300的掩模，，，，把rect矩形叠加进src1矩阵中，rect中的值用scalar修改为255，255，255
  Mat comsrc1, comsrc2;
  min(img0, src1, comsrc1);
  imshow("comsrc1", comsrc1);

  Mat src2 = Mat(512, 512, CV_8UC3,
                 Scalar(0, 0, 255)); // 生成一个显示红色通道的低通掩模
  min(img0, src2, comsrc2);
  imshow("comsrc2", comsrc2);
  return 0;
}
