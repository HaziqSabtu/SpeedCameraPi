/**
 * @file ObjectDetection.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Detecting Objects from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Algorithm/object_detection/ObjectDetection.hpp>

// TODO: Setters and Getters for params
namespace Detection {

/**
 * @brief Construct a new Object Detection:: Object Detection object
 *
 * @param maxCorners maximum number of corners to be detected on init()
 */
ObjectDetection::ObjectDetection(int maxCorners) : maxCorners(maxCorners) {}

/**
 * @brief Set the Detection Parameters to override the default values
 * @details For more information on the parameters, refer to the OpenCV
 * documentation for goodFeaturesToTrack and calcOpticalFlowPyrLK
 * @see <a
 * href="https://docs.opencv.org/3.4/dd/d1a/group__imgproc__feature.html#ga1d6bb77486c8f92d79c8793ad995d541">goodFeaturesToTrack</a>
 * @param maxCorners maximum number of corners to be detected on init()
 * @param qualityLevel parameter characterizing the minimal accepted quality of
 * image corners
 * @param minDistance minimum possible Euclidean distance between the returned
 * corners
 * @param blockSize size of an average block for computing a derivative
 * covariance matrix over each pixel neighborhood
 * @param useHarrisDetector  parameter indicating whether to use a Harris
 * detector (see cornerHarris) or cornerMinEigenVal
 * @param k free parameter of the Harris detector
 * @param minPointDistance minimum distance between points
 */
void ObjectDetection::SetDetectionParams(int maxCorners, double qualityLevel,
                                         double minDistance, int blockSize,
                                         bool useHarrisDetector, double k,
                                         double minPointDistance) {
    this->maxCorners = maxCorners;
    this->qualityLevel = qualityLevel;
    this->minDistance = minDistance;
    this->blockSize = blockSize;
    this->useHarrisDetector = useHarrisDetector;
    this->k = k;
    this->minPointDistance = minPointDistance;
}

Detection::OpticalFlowData ObjectDetection::init(cv::Mat &frame,
                                                 cv::Mat &mask) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::goodFeaturesToTrack(gray, points, maxCorners, qualityLevel, minDistance,
                            mask, blockSize, useHarrisDetector, k);
    return Detection::OpticalFlowData(gray, points);
}

Detection::OpticalFlowData
ObjectDetection::updateFlow(cv::Mat &currentFrame,
                            Detection::OpticalFlowData &prevFlowData) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    std::vector<uchar> status;
    std::vector<float> err;

    cv::Mat prevGray = prevFlowData.gray;
    std::vector<cv::Point2f> prevPoints = prevFlowData.GetPoints();

    cv::cvtColor(currentFrame, gray, cv::COLOR_BGR2GRAY);
    cv::calcOpticalFlowPyrLK(prevGray, gray, prevPoints, points, status, err);

    Detection::OpticalFlowData flow(gray);
    flow.push(prevFlowData, points, err, status);
    return flow;
}

} // namespace Detection
