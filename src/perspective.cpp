#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

float w = 250, h = 350;
Mat matrix, imgWarp;

int main() {
  string path = "/home/megumin/code/opencv/opencv4/resources/cards.jpg";
  Mat img = imread(path);

  Point2f src[4] = {{62, 309}, {321, 265}, {89, 597}, {381, 541}};
  Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

  matrix = getPerspectiveTransform(src, dst); // Perspective -> 透视
  warpPerspective(img, imgWarp, matrix, Point(w, h));

  for (int i = 0; i < 4; i++) {
    circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
  }

  imshow("Image", img);
  imshow("ImageWarp", imgWarp);
  while(waitKey(10) != 'q' || 27);

  return 0;
}