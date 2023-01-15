#ifndef SPARSE_OPTICALFLOW_HPP
#define SPARSE_OPTICALFLOW_HPP

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>

struct PointData {
    // point is location of the point to track
    // status is true if the point is being tracked correctly
    cv::Point2f point;
    uchar status;
    float err;
};

class SparseOF {

  private:
    cv::TermCriteria criteria;
    cv::RNG rng;

    // TermCriteria Parameter
    cv::TermCriteria::Type criteriaType =
        cv::TermCriteria::Type(cv::TermCriteria::COUNT | cv::TermCriteria::EPS);
    // cv::TermCriteria::Type criteriaType = cv::TermCriteria::Type(
    //     (cv::TermCriteria::COUNT) + (cv::TermCriteria::EPS));

    int maxCount = 20;
    double epsilon = 0.03;

    // Lucas Kanade Parameter
    cv::Size winSize = cv::Size(15, 15);
    int maxLevel = 3;
    // int maxLevel = 2;

    // Feature Tracking Parameter
    int maxCorners = 500;
    double qualityLevel = 0.1;
    double minDistance = 7;
    int blockSize = 7;
    bool useHarrisDetector = false;
    double k = 0.04;

    /* data */
    cv::Mat mask;
    cv::Mat output;
    cv::Mat prevGray;
    cv::Rect roi;
    std::vector<float> err;
    std::vector<uchar> status;
    std::vector<cv::Scalar> colors;
    std::vector<cv::Point2f> roiPoints;
    std::vector<cv::Point2f> initialPoints;
    std::vector<cv::Point2f> trackingPoints;
    std::vector<cv::Point2f> processedPoints;
    std::vector<std::vector<PointData>> collection;

  public:
    SparseOF();
    ~SparseOF();
    void Init(const cv::Mat &frame, cv::Rect &_roi);
    void setInitialPoints();
    void run(const cv::Mat &frame);
    void pushCollection(std::vector<cv::Point2f> &points);
    void pushCollection(std::vector<cv::Point2f> &points,
                        std::vector<uchar> &status, std::vector<float> &err);
    void setRoiPoints(const cv::Rect &roi);
    void drawPoints(const cv::Mat &frame);

    void updatePrevVariables(const cv::Mat &g,
                             const std::vector<cv::Point2f> &p);
    std::vector<std::vector<PointData>> evaluateCollection();
    bool isROIEmpty();
    void clearVector();
    std::vector<std::vector<PointData>> getCollection();
    cv::Rect getRoi();
    cv::Mat getOutput();
    cv::Mat getMask();
    void frameSkip(std::vector<std::vector<PointData>> &pointData, int skip);
};

#endif