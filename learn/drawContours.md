`cv::drawContours` 是 OpenCV 中一个非常有用的函数，用于在图像上绘制轮廓。这个函数可以将一个或多个轮廓（即边界曲线）绘制到图像上，常用于图像分析和处理，特别是在物体检测、边缘识别、形态学操作等领域。

```cpp
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    // 创建一张空白图像
    cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3);

    // 创建两个简单的轮廓（一个矩形和一个圆形）
    std::vector<std::vector<cv::Point>> contours;
    
    // 矩形轮廓
    contours.push_back({cv::Point(100, 100), cv::Point(400, 100), cv::Point(400, 400), cv::Point(100, 400)});
    
    // 圆形轮廓
    std::vector<cv::Point> circle;
    for (int angle = 0; angle < 360; angle += 10) {
        circle.push_back(cv::Point(250 + 100 * cos(angle * CV_PI / 180), 250 + 100 * sin(angle * CV_PI / 180)));
    }
    contours.push_back(circle);

    // 绘制所有轮廓，绿色，粗细为2
    cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 0), 2);

    // 显示图像
    cv::imshow("Contours", image);
    cv::waitKey(0);
    return 0;
}
```