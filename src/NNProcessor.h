//
// Created by ishu on 4/4/20.
//

#ifndef IMAGEPROC_NNPROCESSOR_H
#define IMAGEPROC_NNPROCESSOR_H
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

class NNProcessor {
public:
  NNProcessor(std::string configPath, std::string binPath);
  void processFrames(cv::Mat &frame, float threshold);

private:
  const size_t inWidth = 300;
  const size_t inHeight = 300;
  const double inScaleFactor = 1.0;
  const cv::Scalar meanVal{104.0, 177.0, 123.0};
  const float minConfidence = 0.5;
  cv::dnn::Net neuralNetwork;
};

#endif // IMAGEPROC_NNPROCESSOR_H
