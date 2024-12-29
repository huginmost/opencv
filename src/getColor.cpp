#include <opencv2/opencv.hpp>
using namespace cv;

#define outputLine() std::cout << "---------------------" << std::endl

int main(int argc, char const *argv[]) {
  cv::Mat img(3, 4, CV_8UC3, cv::Scalar(0, 0, 1));

  cv::Vec3b vc3 = img.at<cv::Vec3b>(0, 0);
  int first = (int)vc3.val[0];
  int second = (int)vc3.val[1];
  int third = (int)vc3.val[2];
  std::cout << first << " " << second << " " << third << "" << std::endl;
  outputLine();

  for (int i = 0; i < img.rows; i++) {
    uchar* ptr = img.ptr<uchar>(i); 
    for (int j = 0; j < img.cols*img.channels(); j++) {
      std::cout << (int)ptr[j] << " ";
    }
    std::cout << std::endl;
  }
  outputLine();
  cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();//mat是什么类型，就要用什么类型的iterator接受指针，不然会报错
  cv::MatIterator_<cv::Vec3b> it_end = img.end<cv::Vec3b>();
  for (int i = 0; it != it_end; it++) {
    std::cout << *it << " ";//可以直接输出 vec3b 类型的值 <- *it
    if ((++i % img.cols) == 0) {
      std::cout << std::endl;
    }
  }
  outputLine();
  std::cout << (int)(*(img.data + img.step[0] * 1 + img.step[1] * 1 + 1)) << std::endl;
  return 0;
}
