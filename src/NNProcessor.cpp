//
// Created by ishu on 4/4/20.
//
#include "NNProcessor.h"
#include <math.h>
using std::cerr;
using cv::Point;
using cv::Scalar;
using std::to_string;
NNProcessor::NNProcessor(std::string configPath, std::string binPath) {
  neuralNetwork = cv::dnn::readNetFromCaffe(configPath, binPath);
  if (neuralNetwork.empty()) {
    cerr << "Can't load network by using the following files: ";
    exit(-1);
  }
}
void NNProcessor::processFrames(cv::Mat &frame, float threshold) {
  cv::Mat blob = cv::dnn::blobFromImage(
      frame, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, false, false);
  neuralNetwork.setInput(blob, "data");
  cv::Mat detection = neuralNetwork.forward("detection_out");

//  std::vector<double> layersTimings;
//  double freq = cv::getTickFrequency() / 1000;
//  double time = neuralNetwork.getPerfProfile(layersTimings) / freq;
//  std::string fpsText("FPS: " +to_string(1000/time) +" ; time: " + to_string(time) + " ms");
//  putText(frame, fpsText, Point(20,20), 0, 0.5, Scalar(0,0,255));
  cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F,
                       detection.ptr<float>());
  for (int i = 0; i < detectionMat.rows; i++) {
    //      cout << detectionMat<< '\n';
    float confidence = detectionMat.at<float>(i, 2);

    if (confidence > threshold) {
      int xLeftBottom =
          static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
      int yLeftBottom =
          static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
      int xRightTop =
          static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
      int yRightTop =
          static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

      cv::Rect object((int)xLeftBottom, (int)yLeftBottom,
                      (int)(xRightTop - xLeftBottom),
                      (int)(yRightTop - yLeftBottom));

      rectangle(frame, object, cv::Scalar(0, 255, 0));
      std::string label("Face: " +
                        std::to_string(round(confidence * 100) / 100.0));

      int baseLine = 0;
      cv::Size labelSize =
          getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
      rectangle(
          frame,
          cv::Rect(cv::Point(xLeftBottom, yLeftBottom - labelSize.height),
                   cv::Size(labelSize.width, labelSize.height + baseLine)),
          cv::Scalar(255, 255, 255), cv::FILLED);
      putText(frame, label, cv::Point(xLeftBottom, yLeftBottom),
              cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
    }
  }
}
