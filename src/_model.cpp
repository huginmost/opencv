#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define outputLine() std::cout << "---------------------" << std::endl
#define ESC 27

int main(int argc, char const *argv[]) {
  string path = "../resources/cards.jpg";
  Mat img = imread(path);

  imshow("Image", img);
  while(waitKey(10) != 'q' || ESC);
  return 0;
}
