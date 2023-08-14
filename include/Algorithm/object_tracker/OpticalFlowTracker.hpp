/**
 * @file OFTracker.hpp
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

#include "Algorithm/object_tracker/ObjectTracker.hpp"
#include <Algorithm/object_tracker/OpticalFlowData.hpp>
#include <Utils/DataStruct.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

/**
 * @brief Class for Detecting Objects from Image using Optical Flow
 */
class OFTracker : public IObjectTracker {

  private:
    // Feature detection Params
    int maxCorners = 1000;
    double qualityLevel = 0.05;
    double minDistance = 7;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    double minPointDistance = 0.2;
    double threshold = 0.2;

  public:
    OFTracker();

    std::vector<cv::Rect> track(std::vector<cv::Mat> &images,
                                cv::Rect rect) override;

    void SetMaxCorners(int maxCorners);
    int GetMaxCorners() const;

    void SetQualityLevel(double qualityLevel);
    double GetQualityLevel() const;

    void SetMinDistance(double minDistance);
    double GetMinDistance() const;

    void SetBlockSize(int blockSize);
    int GetBlockSize() const;

    void SetUseHarrisDetector(bool useHarrisDetector);
    bool GetUseHarrisDetector() const;

    void SetK(double k);
    double GetK() const;

    void SetMinPointDistance(double minPointDistance);
    double GetMinPointDistance() const;

    void SetThreshold(double threshold);
    double GetThreshold() const;

  private:
    OpticalFlowData init(cv::Mat &frame, cv::Mat &mask);
    OpticalFlowData updateFlow(cv::Mat &currentFrame,
                               OpticalFlowData &prevFlowData);
};

/**
 * @example objectDetection.cpp
 * @brief Example of using OFTracker.hpp
 *
 */

#endif