//
// Created by ishu on 4/4/20.
//
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "NNProcessor.h"
using cv::VideoCapture;
using std::cerr;
int main() {
  std::cout << "Hello from nnp\n";
  std::string modelConfiguration = "data/deploy.prototxt.txt";
  std::string modelBinary = "data/res10_300x300_ssd_iter_140000.caffemodel";
  float threshold = 0.7;
  auto net = NNProcessor(modelConfiguration, modelBinary);
  int cameraDevice = 0;
  auto cap = VideoCapture(cameraDevice);
  if (!cap.isOpened()) {
    cerr << "Couldn't find camera: " << cameraDevice << '\n';
    return -1;
  }
  int i = 0;
  while (true) {
    i += 1;
    cv::Mat frame;
    cap >> frame;
    if (i % 2 == 0)
      continue;
    net.processFrames(frame, threshold);
    imshow("detections", frame);
    if (cv::waitKey(1) >= 0)
      break;
  }

  return 0;
}