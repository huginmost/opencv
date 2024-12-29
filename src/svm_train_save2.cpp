#include <filesystem>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace ml;
namespace fs = std::filesystem;

#define outputLine() \
  std::cout << std::endl << "---------------------" << std::endl

// 转换为 SVM 所需格式
Mat processImage(const Mat& img) {
  Mat resizedImg;
  resize(img, resizedImg, Size(32, 32));
  resizedImg = resizedImg.reshape(1, 1);     // 展平为一维
  resizedImg.convertTo(resizedImg, CV_32F);  // 转换为 CV_32F 类型
  return resizedImg;
}

int main() {
  std::string directoryPath = "/home/megumin/code/test_assets/roi_gray";
  Mat trainData, trainLabel;
  size_t num = 0, size = 0, imgVectorLen = 32 * 32;

  for (const auto& entry : fs::directory_iterator(directoryPath)) {
    for (const auto& file : fs::directory_iterator(entry.path().string())) {
      ++size;
    }
  }

  trainData = Mat::zeros(size, 32 * 32, CV_32F);

  for (const auto& entry : fs::directory_iterator(directoryPath)) {
    int label = std::stoi(entry.path().filename());

    for (const auto& file : fs::directory_iterator(entry.path().string())) {
      Mat img = imread(file.path().string(), IMREAD_GRAYSCALE);

      auto proImg = processImage(img);
      trainLabel.push_back(Mat::ones(1, 1, CV_32S) * label);  // 标签
      memcpy(trainData.data + num++ * imgVectorLen * sizeof(float), proImg.data,
             imgVectorLen * sizeof(float));
    }
  }

  Ptr<ml::SVM> svm = ml::SVM::create();

  // 多分类
  svm->setType(SVM::C_SVC);
  // kernal选用RBF
  svm->setKernel(SVM::RBF);
  // 设置经验值
  svm->setGamma(0.01);
  svm->setC(10.0);
  // 设置终止条件，在这里选择迭代200次
  svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 200, FLT_EPSILON));
  // 训练开始

  svm->train(trainData, ml::ROW_SAMPLE, trainLabel);

  std::cout << "finished" << std::endl;

  // Mat testSample = imread("/home/megumin/code/test_assets/roi_gray/2/99.png",
  // IMREAD_GRAYSCALE); imshow("Test", testSample); testSample =
  // processImage(testSample);

  svm->save("svm_model2.xml");

  // waitKey(0);
  return 0;
}
