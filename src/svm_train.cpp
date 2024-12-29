#include <filesystem>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
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

void saveSVMData(const Mat& trainData, const Mat& trainLabel,
                 const std::string& fileName) {
  FileStorage fs(fileName, FileStorage::WRITE);
  fs << "trainData" << trainData;
  fs << "trainLabel" << trainLabel;
}

void loadSVMData(Mat& trainData, Mat& trainLabel, const std::string& fileName) {
  FileStorage fs(fileName, FileStorage::READ);
  fs["trainData"] >> trainData;
  fs["trainLabel"] >> trainLabel;
}

int main() {
  std::string directoryPath = "/home/megumin/code/test_assets/roi_gray";
  Mat trainData, trainLabel;

  std::string trainFile = "svm_train.xml.gz";

  if (std::filesystem::exists(trainFile)) {
    loadSVMData(trainData, trainLabel, trainFile);
  } else {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      int label = std::stoi(entry.path().filename());

      for (const auto& file : fs::directory_iterator(entry.path().string())) {
        Mat img = imread(file.path().string(), IMREAD_GRAYSCALE);

        trainData.push_back(processImage(img));
        trainLabel.push_back(Mat::ones(1, 1, CV_32S) * label);
      }
    }
    saveSVMData(trainData, trainLabel, trainFile);
  }

  Ptr<ml::SVM> svm = ml::SVM::create();

  // svm 超参数设置
  svm->setKernel(ml::SVM::LINEAR);  // 使用线性核
  svm->setType(ml::SVM::C_SVC);     // 使用 C-SVC
  svm->setTermCriteria(
      TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));  // 设置终止准则
  svm->train(trainData, ml::ROW_SAMPLE, trainLabel);
  std::cout << "completed" << std::endl;

  Mat testSample = imread("/home/megumin/code/test_assets/roi_gray/6/20.png",
                          IMREAD_GRAYSCALE);
  imshow("test", testSample);
  testSample = processImage(testSample);

  // predict
  int response = svm->predict(testSample);
  std::cout << "response:" << response << std::endl;

  waitKey(0);
  return 0;
}
