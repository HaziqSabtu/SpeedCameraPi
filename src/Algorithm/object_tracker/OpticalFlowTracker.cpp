/**
 * @file OFTracker.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Detecting Objects from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Algorithm/object_tracker/OpticalFlowTracker.hpp"

/**
 * @brief Construct a new Object Detection:: Object Detection object
 *
 */
OFTracker::OFTracker() {}

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

OpticalFlowData OFTracker::init(cv::Mat &frame, cv::Mat &mask) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::goodFeaturesToTrack(gray, points, maxCorners, qualityLevel, minDistance,
                            mask, blockSize, useHarrisDetector, k);
    return OpticalFlowData(gray, points);
}

OpticalFlowData OFTracker::updateFlow(cv::Mat &currentFrame,
                                      OpticalFlowData &prevFlowData) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    std::vector<uchar> status;
    std::vector<float> err;

    cv::Mat prevGray = prevFlowData.gray;
    std::vector<cv::Point2f> prevPoints = prevFlowData.GetPoints();

    cv::cvtColor(currentFrame, gray, cv::COLOR_BGR2GRAY);
    cv::calcOpticalFlowPyrLK(prevGray, gray, prevPoints, points, status, err);

    OpticalFlowData flow(gray);
    flow.push(prevFlowData, points, err, status);
    return flow;
}

std::vector<cv::Rect> OFTracker::track(std::vector<cv::Mat> &images,
                                       cv::Rect rect) {
    std::vector<OpticalFlowData> flowData;

    const int FRAME_COUNT = images.size();

    // create mask for ROI
    cv::Mat mask = cv::Mat::zeros(images.at(0).size(), CV_8UC1);
    if (rect.area() > 0) {
        mask(rect).setTo(255);
    }

    flowData.push_back(init(images.at(0), mask));

    for (int i = 1; i < FRAME_COUNT; i++) {
        flowData.push_back(updateFlow(images.at(i), flowData.at(i - 1)));
    }

    // * IDEA: Imagine Point moving in 3D space
    // * The moving points can be seen clearly ?
    // * Seperate with KNN CLustering
    std::vector<int> ids;
    for (int i = 0; i < flowData.at(0).GetPoints().size(); i++) {
        ids.push_back(i);
    }

    for (int i = 1; i < FRAME_COUNT; i++) {
        flowData.at(i).thresholdPointsId(ids, flowData.at(i - 1), threshold);
    }

    // Return empty vector if no objects are detected
    if (ids.size() == 0) {
        return std::vector<cv::Rect>();
    }

    // Track the movement of the objects
    std::vector<cv::Rect> trackedObjects;
    for (int i = 0; i < FRAME_COUNT; i++) {
        auto points = flowData.at(i).GetPointsById(ids);

        //fit rectangle
        std::vector<cv::Point2f> ps;

        for (auto p : points) {
            ps.push_back(p.point);
        }

        cv::Rect rect = cv::boundingRect(ps);
        trackedObjects.push_back(rect);
    }
    return trackedObjects;
}

void OFTracker::SetMaxCorners(int maxCorners) { this->maxCorners = maxCorners; }

int OFTracker::GetMaxCorners() const { return maxCorners; }

void OFTracker::SetQualityLevel(double qualityLevel) {
    this->qualityLevel = qualityLevel;
}

double OFTracker::GetQualityLevel() const { return qualityLevel; }

void OFTracker::SetMinDistance(double minDistance) {
    this->minDistance = minDistance;
}

double OFTracker::GetMinDistance() const { return minDistance; }

void OFTracker::SetBlockSize(int blockSize) { this->blockSize = blockSize; }

int OFTracker::GetBlockSize() const { return blockSize; }

void OFTracker::SetUseHarrisDetector(bool useHarrisDetector) {
    this->useHarrisDetector = useHarrisDetector;
}

bool OFTracker::GetUseHarrisDetector() const { return useHarrisDetector; }

void OFTracker::SetK(double k) { this->k = k; }

double OFTracker::GetK() const { return k; }

void OFTracker::SetMinPointDistance(double minPointDistance) {
    this->minPointDistance = minPointDistance;
}

double OFTracker::GetMinPointDistance() const { return minPointDistance; }

void OFTracker::SetThreshold(double threshold) { this->threshold = threshold; }

double OFTracker::GetThreshold() const { return threshold; }
