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

#include <Algorithm/object_tracker/OpticalFlowTracker.hpp>

/**
 * @brief Construct a new Object Detection:: Object Detection object
 *
 * @param rng random number generator
 * @param maxCorners maximum number of corners to be detected
 */
ObjectObjectDetection(cv::RNG rng, int maxCorners) : rng(rng) {
    this->maxCorners = maxCorners;
    for (int i = 0; i < maxCorners; i++) {
        colors.push_back(cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
                                    rng.uniform(0, 255)));
    }
}

/**
 * @overload ObjectObjectDetection(rng, 1000)
 */
ObjectObjectDetection(cv::RNG rng) : ObjectDetection(rng, 1000) {}

/**
 * @brief Initialize Optical Flow
 *
 * @param firstImage first image to be processed
 */
void ObjectDetection::runDetection(std::vector<ImageData> &imgData) {
    cv::Mat firstImage = imgData[0].image;
    std::cout << "Initializing Optical Flow" << std::endl;
    initOpticalFlow(firstImage);
    std::cout << "Optical Flow Initialized" << std::endl;
    for (int i = 1; i < imgData.size(); i++) {
        std::cout << "Frame: " << i << std::endl;
        refreshVectors();
        frame = imgData[i].image;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        std::cout << "Old Points Size: " << oldPoints.size() << std::endl;
        cv::calcOpticalFlowPyrLK(oldGray, gray, oldPoints, points, status, err);
        std::vector<cv::Point2f> goodPoints;
        std::vector<int> deletedIDs;

        for (uint i = 0; i < oldPoints.size(); i++) {
            if (isPointValid(i)) {
                goodPoints.push_back(points[i]);
                opticalFlowPoints[i].push_back(points[i]);
                continue;
            }
            deletedIDs.push_back(i);
        }

        if (deletedIDs.size() > 0) {
            removeUntrackedPoints(deletedIDs);
        }

        copyOldData(goodPoints);
    }

    std::cout << "Optical Flow Finished" << std::endl;
    std::cout << "Optical Flow Points Size: " << opticalFlowPoints.size()
              << std::endl;
}

/**
 * @brief Get the Result of the Object Detection
 * @param points points of the object from optical flow
 * @return cv::Rect& rectangle of the detected object
 */
cv::Rect &ObjectDetection::GetRect(const std::vector<cv::Point2f> &points) {
    bbox = cv::boundingRect(points);
    return bbox;
}

/**
 * @brief Set the Minimum Point Distance of Point
 *
 * @param minPointDistance minimum distance moved by the point between frames to
 * consider as valid moving point
 */
void ObjectDetection::SetMinPointDistance(double minPointDistance) {
    this->minPointDistance = minPointDistance;
}

/**

* @brief Returns a line with two points, representing the bottom edge of the
Bounding Box from Object Detection.
* @param points Vector of points from result of object detection.
* @param width Width of the image.
* @return std::vectorcv::Point2f& Reference to the bottom line points.
*/
std::vector<cv::Point2f> &
ObjectDetection::GetBottomLine(const std::vector<cv::Point2f> &points,
                               int width) {
    bottomLine.clear();
    std::vector<cv::Point2f> tmp;
    tmp.assign(points.begin(), points.end());
    std::sort(tmp.begin(), tmp.end(),
              [](cv::Point2f a, cv::Point2f b) { return a.y > b.y; });
    cv::Point2f mostBottomLine = tmp.front();
    bottomLine.push_back(cv::Point2f(0, mostBottomLine.y));
    bottomLine.push_back(
        cv::Point2f(static_cast<float>(width), mostBottomLine.y));
    return bottomLine;
}

std::vector<std::vector<cv::Point2f>> &ObjectDetection::GetOFPoints(
    const std::vector<std::vector<cv::Point2f>> &opticalFlowPoints, int count) {
    result.clear();
    result.assign(opticalFlowPoints.begin(),
                  opticalFlowPoints.begin() + count + 1);
    return result;
}

/**
 * @brief Get the Result of the Object Detection in the form of vector of
 * points
 *
 * @param reshape whether to reshape the vector of points to be 2D vector
 * @return std::vector<std::vector<cv::Point2f>> vector of points from optical
 * flow
 */
std::vector<std::vector<cv::Point2f>>
ObjectDetection::GetOpticalFlowPoints(bool reshape) {
    return reshape ? reshapeVectors(opticalFlowPoints) : opticalFlowPoints;
}

void ObjectDetection::initOpticalFlow(cv::Mat &frame) {
    oldFrame = frame.clone();
    cv::cvtColor(oldFrame, oldGray, cv::COLOR_BGR2GRAY);
    cv::Mat mask = cv::Mat::zeros(oldFrame.size(), oldFrame.type());

    cv::goodFeaturesToTrack(oldGray, oldPoints, maxCorners, qualityLevel,
                            minDistance, cv::Mat(), blockSize,
                            useHarrisDetector, k);

    for (cv::Point2f p : oldPoints) {
        std::vector<cv::Point2f> tmp;
        tmp.push_back(p);
        opticalFlowPoints.push_back(tmp);
    }
}

void ObjectDetection::copyOldData(std::vector<cv::Point2f> goodPoints) {
    oldGray = gray.clone();
    oldPoints.clear();
    oldPoints.assign(goodPoints.begin(), goodPoints.end());
}

bool ObjectDetection::isPointValid(int i) {
    return status[i] == 1 &&
           distance(oldPoints[i], points[i]) >= minPointDistance;
}

void ObjectDetection::removeUntrackedPoints(std::vector<int> &deletedIDs) {
    opticalFlowPoints.erase(
        std::remove_if(opticalFlowPoints.begin(), opticalFlowPoints.end(),
                       [&](std::vector<cv::Point2f> &v) {
                           return std::find(deletedIDs.begin(),
                                            deletedIDs.end(),
                                            &v - &opticalFlowPoints[0]) !=
                                  deletedIDs.end();
                       }),
        opticalFlowPoints.end());
}

double ObjectDetection::distance(cv::Point2f p1, cv::Point2f p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void ObjectDetection::refreshVectors() {
    points.clear();
    status.clear();
    err.clear();
}

std::vector<std::vector<cv::Point2f>> ObjectDetection::reshapeVectors(
    std::vector<std::vector<cv::Point2f>> &vectors) {
    size_t m = vectors.size();
    size_t n = vectors[0].size();
    std::vector<std::vector<cv::Point2f>> reshapedVectors(
        n, std::vector<cv::Point2f>(m));

    for (int i = 0; i < m; i++) {
        std::cout << "i = " << i << std::endl;
        std::vector<cv::Point2f> tmp;
        for (int j = 0; j < n; j++) {
            reshapedVectors[j][i] = vectors[i][j];
        }
    }
    return reshapedVectors;
}
