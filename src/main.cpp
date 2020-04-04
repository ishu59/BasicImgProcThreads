#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "utils/MultipleImageWindow.h"
using namespace cv;

void blurImg(const Mat &img, Mat &blurMat) {
  //  int a = 0;
  blur(img, blurMat, Size(5, 5));
}
void grayImg(const Mat &img, Mat &grayMat) {
  cvtColor(img, grayMat, COLOR_BGR2GRAY);
}
void sobelImg(const Mat &img, Mat &sobelMat) {
  Sobel(img, sobelMat, CV_8U, 1, 1);
}

int main() {
  VideoCapture cap;
  cap.open(0);
  namedWindow("Video", 1);
  std::unique_ptr<MultipleImageWindow> miw;
  while (true) {

    Mat frame;
    cap >> frame;
    miw = make_unique<MultipleImageWindow>("MainWindow", 2, 2, WINDOW_AUTOSIZE);
    vector<thread> tVec;
    Mat blurMat, grayMat, sobelMat;
    tVec.emplace_back(thread(blurImg, std::ref(frame), std::ref(blurMat)));
    tVec.emplace_back(thread(grayImg, std::ref(frame), std::ref(grayMat)));
    tVec.emplace_back(thread(sobelImg, std::ref(frame), std::ref(sobelMat)));
    for(auto& v:tVec){
      v.join();
    }
    miw->addImage("Main", frame);
    miw->addImage("Gray", grayMat);
    miw->addImage("Blur", blurMat);
    miw->addImage("Sobel", sobelMat);
    miw->render();
//    imshow("Video", frame);
    if (waitKey(30) >= 0) {
      break;
    }
  }
  cap.release();
  return 0;
}
