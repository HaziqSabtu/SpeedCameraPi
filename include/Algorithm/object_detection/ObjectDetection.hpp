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
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
class ObjectDetection {

  private:
    std::vector<cv::Scalar> colors;
    cv::RNG rng;

    cv::Mat oldFrame;
    cv::Mat oldGray;
    cv::Mat frame;
    cv::Mat gray;

    std::vector<cv::Point2f> oldPoints;
    std::vector<cv::Point2f> points;
    std::vector<uchar> status;
    std::vector<float> err;
    std::vector<std::vector<cv::Point2f>> opticalFlowPoints;

    cv::Mat mask;

    // Feature detection Params
    int maxCorners = 1000;
    double qualityLevel = 0.05;
    double minDistance = 7;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    double minPointDistance = 0.2;

    cv::Rect bbox;
    std::vector<std::vector<cv::Point2f>> result;
    std::vector<cv::Point2f> bottomLine;

  public:
    ObjectDetection(cv::RNG rng, int maxCorners);

    ObjectDetection(cv::RNG rng);

    void runDetection(std::vector<ImageData> &imgData);

    void SetMinPointDistance(double minPointDistance);

    std::vector<std::vector<cv::Point2f>>
    GetOpticalFlowPoints(bool reshape = false);

    cv::Rect &GetRect(const std::vector<cv::Point2f> &points);

    std::vector<cv::Point2f> &
    GetBottomLine(const std::vector<cv::Point2f> &points, int width);

    std::vector<std::vector<cv::Point2f>> &
    GetOFPoints(const std::vector<std::vector<cv::Point2f>> &opticalFlowPoints,
                int count);

  private:
    void initOpticalFlow(cv::Mat &frame);

    void copyOldData(std::vector<cv::Point2f> goodPoints);

    bool isPointValid(int i);

    void removeUntrackedPoints(std::vector<int> &deletedIDs);

    static double distance(cv::Point2f p1, cv::Point2f p2);

    void refreshVectors();

    static std::vector<std::vector<cv::Point2f>>
    reshapeVectors(std::vector<std::vector<cv::Point2f>> &vectors);
};

#endif