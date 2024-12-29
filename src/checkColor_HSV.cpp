#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// 全局变量
Mat img, imgHSV, mask;

// 回调函数：滑动条触发时调用
void on_trackbar(int, void*) {
	// 传入的参数不被使用，可以只写个参数类型上去，而不用加参数名

  // 获取滑动条当前值
  int hmin = getTrackbarPos("Hue Min", "Trackbars");
  int hmax = getTrackbarPos("Hue Max", "Trackbars");
  int smin = getTrackbarPos("Sat Min", "Trackbars");
  int smax = getTrackbarPos("Sat Max", "Trackbars");
  int vmin = getTrackbarPos("Val Min", "Trackbars");
  int vmax = getTrackbarPos("Val Max", "Trackbars");

  // 定义 HSV 范围
  Scalar lower(hmin, smin, vmin);
  Scalar upper(hmax, smax, vmax);

  // 使用 inRange 将图像中符合颜色范围的像素标记为白色（255），其他像素标记为黑色（0）
  inRange(imgHSV, lower, upper, mask);

  // 显示掩膜图像
  imshow("Image Mask", mask);
}

int main() {
  // 加载图像
  string path = "../resources/lambo.png";
  img = imread(path);
  if (img.empty()) {
    cerr << "Error: Image not found!" << endl;
    return -1;
  }

  // 转换到 HSV 色彩空间
  cvtColor(img, imgHSV, COLOR_BGR2HSV);

  // 创建显示窗口
  namedWindow("Trackbars", (450, 200));
  imshow("Image", img);
  imshow("Image HSV", imgHSV);

  // 创建滑动条，不使用指针
  createTrackbar("Hue Min", "Trackbars", 0, 179, on_trackbar);
  createTrackbar("Hue Max", "Trackbars", 0, 179, on_trackbar);
  createTrackbar("Sat Min", "Trackbars", 0, 255, on_trackbar);
  createTrackbar("Sat Max", "Trackbars", 0, 255, on_trackbar);
  createTrackbar("Val Min", "Trackbars", 0, 255, on_trackbar);
  createTrackbar("Val Max", "Trackbars", 0, 255, on_trackbar);

  // 初始值设定
  setTrackbarPos("Hue Min", "Trackbars", 0);
  setTrackbarPos("Hue Max", "Trackbars", 19);
  setTrackbarPos("Sat Min", "Trackbars", 110);
  setTrackbarPos("Sat Max", "Trackbars", 240);
  setTrackbarPos("Val Min", "Trackbars", 153);
  setTrackbarPos("Val Max", "Trackbars", 255);

  // 手动调用回调函数，显示初始掩膜
  // on_trackbar(0, 0);

  while (waitKey(10) != 'g')
    ;

  return 0;
}
