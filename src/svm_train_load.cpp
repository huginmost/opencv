#include <filesystem>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
namespace fs = std::filesystem;

#define outputLine() \
  std::cout << std::endl << "---------------------" << std::endl

Mat processImage(const Mat& img) {
  Mat resizedImg;
  resize(img, resizedImg, Size(32, 32));
  resizedImg = resizedImg.reshape(1, 1);     // Flatten to 1D
  resizedImg.convertTo(resizedImg, CV_32F);  // Convert to CV_32F type
  return resizedImg;
}

int main(int argc, char const* argv[]) {
  Mat testSample = imread("/home/megumin/code/test_assets/roi_gray/5/1.png", IMREAD_GRAYSCALE);
  imshow("Test", testSample);
  testSample = processImage(testSample);

  Ptr<ml::SVM> svm = ml::SVM::load("svm_model.xml");

  Mat rawResponse;
  auto response = svm->predict(testSample, rawResponse, ml::StatModel::RAW_OUTPUT);

  std::cout << "Raw decision value (similarity score): " << rawResponse.at<float>(0, 0) << std::endl;
  std::cout << "Predicted class label: " << response << std::endl;

  waitKey(0);
  return 0;
}
