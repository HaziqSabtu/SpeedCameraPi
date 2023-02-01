#ifndef OBJECT_DETECTION_HPP
#define OBJECT_DETECTION_HPP

#include <Utils/fileWR.hpp>
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
    double minPointDistance = 0.4;

  public:
    ObjectDetection(cv::RNG rng, int maxCorners);

    ObjectDetection(cv::RNG rng);

    void runDetection(const std::vector<ImgData> &imgData);

    void SetMinPointDistance(double minPointDistance);

    std::vector<std::vector<cv::Point2f>>
    GetOpticalFlowPoints(bool reshape = false);

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