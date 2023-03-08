/**
 * @file OD.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Detecting Objects from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Algorithm/object_detection/ObjectDetection2.hpp>

namespace Detection {
OD::OD(int maxCorners) : maxCorners(maxCorners) {}

Detection::OpticalFlowData OD::init(cv::Mat &frame) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::goodFeaturesToTrack(gray, points, maxCorners, qualityLevel, minDistance,
                            cv::Mat(), blockSize, useHarrisDetector, k);
    return Detection::OpticalFlowData(gray, points);
}

Detection::OpticalFlowData OD::updateFlow(ImageData &current,
                                          ImageData &previous) {
    cv::Mat gray;
    std::vector<cv::Point2f> points;
    std::vector<uchar> status;
    std::vector<float> err;

    cv::Mat prevGray = previous.flow.gray;
    std::vector<cv::Point2f> prevPoints = previous.flow.GetPoints();

    cv::cvtColor(current.image, gray, cv::COLOR_BGR2GRAY);
    cv::calcOpticalFlowPyrLK(prevGray, gray, prevPoints, points, status, err);

    Detection::OpticalFlowData flow(gray);
    flow.push(previous.flow, points, err, status);
    return flow;
}

void OD::detect(std::vector<cv::Mat> &frames) {
    Detection::OpticalFlowData prevData = init(frames[0]);
    for (int i = 1; i < frames.size(); i++) {
        Detection::OpticalFlowData currData =
            updateFlow(frames[i], frames[i - 1]);
        currData.threshold(prevData, minPointDistance);
        prevData = currData;
    }
}
} // namespace Detection
