/**
 * @file ObjectDetection.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Detecting Objects from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef OBJECT_DETECTION_HPP
#define OBJECT_DETECTION_HPP

#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_OpticalFlow.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
namespace Detection {
class ObjectDetection {

  private:
    // Feature detection Params
    int maxCorners = 1000;
    double qualityLevel = 0.05;
    double minDistance = 7;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    double minPointDistance = 0.2;

  public:
    ObjectDetection(int maxCorners);
    void SetDetectionParams(int maxCorners, double qualityLevel,
                            double minDistance, int blockSize,
                            bool useHarrisDetector, double k,
                            double minPointDistance);
    Detection::OpticalFlowData init(cv::Mat &frame);
    Detection::OpticalFlowData updateFlow(ImageData &current,
                                          ImageData &previous);
    void detect(std::vector<cv::Mat> &frames);

  private:
};
} // namespace Detection

#endif