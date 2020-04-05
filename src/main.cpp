#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
//using namespace std;

#include "MultWindow.h"
#include "NNProcessor.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
// using namespace cv;

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
void faceTrack(NNProcessor &net,Mat &frame) {
//  std::cout << "Hello from nnp\n";
//  std::string modelConfiguration = "data/deploy.prototxt.txt";
//  std::string modelBinary = "data/res10_300x300_ssd_iter_140000.caffemodel";

//  auto net = NNProcessor(modelConfiguration, modelBinary);
//  int cameraDevice = 0;
//  auto cap = VideoCapture(cameraDevice);

  float threshold = 0.7;
  net.processFrames(frame, threshold);
}
void compute() {
  VideoCapture cap;
  cap.open(0);
  if(!cap.isOpened()) {
    std::cerr << "Unable to open webcam, Please configure webcam as device 0.\n";
    exit(-1);
  }
  std::unique_ptr<MultWindow> miw;
  std::string modelConfiguration = "data/deploy.prototxt.txt";
  std::string modelBinary = "data/res10_300x300_ssd_iter_140000.caffemodel";

  auto net = NNProcessor(modelConfiguration, modelBinary);
  this_thread::sleep_for(chrono::milliseconds(1000));
  int i = 0;
  while (true) {
    ++i;
    Mat frame;
    cap >> frame;
    if (i%2==0)
      continue;
    miw = make_unique<MultWindow>("MainWindow", 2, 2, WINDOW_AUTOSIZE);
    vector<thread> tVec;
    Mat blurMat, grayMat, sobelMat, nnMat;
    frame.copyTo(nnMat);
    tVec.emplace_back(thread(blurImg, std::ref(frame), std::ref(blurMat)));
    tVec.emplace_back(thread(grayImg, std::ref(frame), std::ref(grayMat)));
    tVec.emplace_back(thread(sobelImg, std::ref(frame), std::ref(sobelMat)));
    tVec.emplace_back(thread(faceTrack, std::ref(net),std::ref(nnMat)));
    for (auto &v : tVec) {
      v.join();
    }
    miw->addImage("Main", nnMat);
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
}
int main() {
  compute();
  return 0;
}
