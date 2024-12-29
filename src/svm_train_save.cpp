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
  resizedImg.convertTo(resizedImg, CV_32FC3);  // 转换为 CV_32F 类型
  return resizedImg;
}

int main() {
  std::string directoryPath = "/home/megumin/code/test_assets/roi_gray";
  Mat trainData, trainLabel;

  for (const auto& entry : fs::directory_iterator(directoryPath)) {
    int label = std::stoi(entry.path().filename());

    for (const auto& file : fs::directory_iterator(entry.path().string())) {
      Mat img = imread(file.path().string(), IMREAD_GRAYSCALE);
      if (img.empty()) continue;

      trainData.push_back(processImage(img));
      trainLabel.push_back(Mat::ones(1, 1, CV_32S) * label);  // 标签
    }
    std::cout << trainData.rows << " " << trainData.cols << std::endl;
  }

  Ptr<ml::SVM> svm = ml::SVM::create();

  svm->setKernel(ml::SVM::LINEAR);
  svm->setType(ml::SVM::C_SVC);
  svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

  // svm->setKernel(ml::SVM::RBF);  // 使用 RBF 核函数（适用于非线性分类）
  // svm->setType(ml::SVM::C_SVC);  // C_SVC 类型，用于分类
  // svm->setC(1.0);            // C 参数，控制分类边界的复杂度
  // svm->setGamma(0.5);        // Gamma 参数，控制 RBF 核的宽度

  // // 多分类
  // svm->setType(SVM::C_SVC);
  // // kernal选用RBF
  // svm->setKernel(SVM::RBF);
  // // 设置经验值
  // svm->setGamma(0.01);
  // svm->setC(10.0);
  // // 设置终止条件，在这里选择迭代200次
  // svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 200, FLT_EPSILON));
  // // 训练开始

  svm->train(trainData, ml::ROW_SAMPLE, trainLabel);

  std::cout << "finished" << std::endl;

  // Mat testSample = imread("/home/megumin/code/test_assets/roi_gray/2/99.png",
  // IMREAD_GRAYSCALE); imshow("Test", testSample); testSample =
  // processImage(testSample);

  svm->save("svm_model.xml");

  // waitKey(0);
  return 0;
}
