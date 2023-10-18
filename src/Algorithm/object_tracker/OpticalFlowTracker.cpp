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
 * @brief Initialize the Optical Flow Tracker
 *
 * @details Initialize the Optical Flow Tracker by detecting features in the first frame. This method is required to be run before updateFlow()
 *
 * @param frame First frame to be used for tracking object.
 * @param mask Mask for the ROI (Region where the object is located)
 * @note Error may be thrown if mask is not in 1 channel
 * @note method is currently private
 * @return OpticalFlowData The data representing the initial frame
 */
OpticalFlowData OFTracker::init(cv::Mat &frame, cv::Mat &mask) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::goodFeaturesToTrack(gray, points, maxCorners, qualityLevel, minDistance,
                            mask, blockSize, useHarrisDetector, k);
    return OpticalFlowData(gray, points);
}

/**
 * @brief Update the Optical Flow Tracker
 *
 * @param currentFrame Current frame to be used to track object location
 * @param prevFlowData Previous Optical Flow Data
 * @note prevFlowData must be initialized using init()
 * @note method is currently private
 * @return OpticalFlowData The data representing the current frame
 */
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

/**
 * @brief Track the object in the image
 *
 * @param images Vector of images to be used for tracking
 * @param rect ROI of the object to be tracked
 * 
 * @note This method is not optimized and require refactoring. See source code for explaination
 * @return std::vector<cv::Rect> Vector of Rectangles representing the location of the object in the image. If tracking fails, return empty vector.
 */
std::vector<cv::Rect> OFTracker::track(std::vector<cv::Mat> &images,
                                       cv::Rect rect) {
    std::vector<OpticalFlowData> flowData;

    const int FRAME_COUNT = images.size();

    // create mask for ROI
    cv::Mat mask = cv::Mat::zeros(images.at(0).size(), CV_8UC1);
    if (rect.area() > 0) {
        mask(rect).setTo(255);
    }

    // initialize Optical Flow Data
    flowData.push_back(init(images.at(0), mask));

    // track the object for subsequent frames
    for (int i = 1; i < FRAME_COUNT; i++) {
        flowData.push_back(updateFlow(images.at(i), flowData.at(i - 1)));
    }

    // From here onwards is where refractoring is needed
    // Initialize the ids from all of the points that are detected at first image
    std::vector<int> ids;
    for (int i = 0; i < flowData.at(0).GetPoints().size(); i++) {
        ids.push_back(i);
    }

    // Analyze points location between frames that have same ids
    // e.g points with id 1 in frame 1 and frame 2
    // e.g points with id 2 in frame 1 and frame 2
    // Measure the distance of the points between frames
    // If the distance is less than minPointDistance, remove the points
    // refer to OpticalFlowData::thresholdPointsId()
    for (int i = 1; i < FRAME_COUNT; i++) {
        flowData.at(i).thresholdPointsId(ids, flowData.at(i - 1), threshold);
    }

    // Return empty vector if no objects are detected
    // In some cases, where bad tracking occurs, ids may be empty
    // hence here assumes that no objects are detected
    if (ids.size() == 0) {
        return std::vector<cv::Rect>();
    }

    // Track the movement of the objects
    // if at the end of the tracking, the ids vector is not empty
    // we assume that the tracking is successful
    // e.g ids = {1,2,10,40,54}
    // we track the movement of the points with id 1,2,10,40,54
    // fit rectangle to the points
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

    // return the vector of rectangles
    return trackedObjects;
}

// Getters and Setters

/**
 * @brief Set the Max Corners object
 *
 * @param maxCorners Maximum number of corners to be detected
 */
void OFTracker::SetMaxCorners(int maxCorners) { this->maxCorners = maxCorners; }

/**
 * @brief Get the Max Corners object
 *
 * @return int Maximum number of corners to be detected
 */
int OFTracker::GetMaxCorners() const { return maxCorners; }

/**
 * @brief Set the Quality Level object
 *
 * @param qualityLevel Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal() ) or the Harris function response (see cornerHarris() ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected.
 */
void OFTracker::SetQualityLevel(double qualityLevel) {
    this->qualityLevel = qualityLevel;
}

/**
 * @brief Get the Quality Level object
 *
 * @return double Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal() ) or the Harris function response (see cornerHarris() ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected.
 */
double OFTracker::GetQualityLevel() const { return qualityLevel; }

/**
 * @brief Set the Min Distance object
 *
 * @param minDistance Minimum possible Euclidean distance between the returned corners.
 */
void OFTracker::SetMinDistance(double minDistance) {
    this->minDistance = minDistance;
}

/**
 * @brief Get the Min Distance object
 *
 * @return double Minimum possible Euclidean distance between the returned corners.
 */
double OFTracker::GetMinDistance() const { return minDistance; }

/**
 * @brief Set the Block Size object
 *
 * @param blockSize Size of an average block for computing a derivative covariation matrix over each pixel neighborhood. See cornerEigenValsAndVecs() .
 */
void OFTracker::SetBlockSize(int blockSize) { this->blockSize = blockSize; }

/**
 * @brief Get the Block Size object
 *
 * @return int Size of an average block for computing a derivative covariation matrix over each pixel neighborhood. See cornerEigenValsAndVecs() .
 */
int OFTracker::GetBlockSize() const { return blockSize; }

/**
 * @brief Set the Use Harris Detector object
 *
 * @param useHarrisDetector Parameter indicating whether to use a Harris detector (see cornerHarris()) or cornerMinEigenVal().
 */
void OFTracker::SetUseHarrisDetector(bool useHarrisDetector) {
    this->useHarrisDetector = useHarrisDetector;
}

/**
 * @brief Get the Use Harris Detector object
 *
 * @return true Use Harris detector (see cornerHarris()) or cornerMinEigenVal().
 * @return false Use cornerMinEigenVal().
 */
bool OFTracker::GetUseHarrisDetector() const { return useHarrisDetector; }

/**
 * @brief Set the K object
 *
 * @param k Free parameter of the Harris detector.
 */
void OFTracker::SetK(double k) { this->k = k; }

/**
 * @brief Get the K object
 *
 * @return double Free parameter of the Harris detector.
 */
double OFTracker::GetK() const { return k; }

/**
 * @brief Set the Min Point Distance object
 *
 * @param minPointDistance Minimum distance between two points
 */
void OFTracker::SetMinPointDistance(double minPointDistance) {
    this->minPointDistance = minPointDistance;
}

/**
 * @brief Get the Min Point Distance object
 *
 * @return double Minimum distance between two points
 */
double OFTracker::GetMinPointDistance() const { return minPointDistance; }

/**
 * @brief Set the Threshold object
 *
 * @param threshold Threshold for removing points
 */
void OFTracker::SetThreshold(double threshold) { this->threshold = threshold; }

/**
 * @brief Get the Threshold object
 *
 * @return
 */
double OFTracker::GetThreshold() const { return threshold; }
