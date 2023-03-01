#ifndef LANE_DETECTION_ALGORITHM_HPP
#define LANE_DETECTION_ALGORITHM_HPP

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct DetLine {
    cv::Point2f start;
    cv::Point2f end;
    double angle;
};

struct ROI {
    int pos;
    cv::Point2f start;
    cv::Point2f end;
    double angle;
};

struct PointsData {
    std::vector<cv::Point2f> leftPoints;
    std::vector<cv::Point2f> rightPoints;
    std::vector<cv::Point2f> midPoints;
};

struct ROIDATA {
    cv::Point2f left;
    cv::Point2f right;
    cv::Point2f intersection;
    PointsData pointsData;
    double angleBetween;
    double midAngle;
};

struct LineCombination {
    int id;
    DetLine left;
    std::vector<cv::Point2f> pointLeft;
    DetLine right;
    std::vector<cv::Point2f> pointRight;
    cv::Point2f intersection;
    std::vector<cv::Point2f> midPoints;
    double midAngle;
    double angleBetween;
};

struct EvaluationData {
    LineCombination lineCombination;
    double error;
};

class LaneDetectionAlgorithm {

  private:
    // HLS Parameters
    int hLow = 0;
    int hHigh = 255;

    int lLow = 120;
    int lHigh = 255;

    int sLow = 0;
    int sHigh = 255;

    // blur Parameters
    int blurKernelSize = 3;
    double blurSigmaX = 0;
    double blurSigmaY = 0;

    // canny Parameters
    int cannyThreshold1 = 100;
    int cannyThreshold2 = 200;
    int cannyApertureSize = 3;

    // HoughLineP Parameters
    int houghThreshold = 50;
    double houghMinLineLength = 10;
    double houghMaxLineGap = 300;
    std::vector<cv::Vec4i> HoughLineOutput;

    int imgGenCount = 0;
    int selectedEvalData = 0;

    int imgGenCountLeft = 0;

    cv::Mat frame;
    cv::Mat hlsFrame;
    cv::Mat hlsMask;
    cv::Mat hlsOutput;
    cv::Mat grayFrame;
    cv::Mat blurFrame;
    cv::Mat cannyFrame;

    ROIDATA roiData;
    std::vector<DetLine> detectedLines;
    std::vector<DetLine> filteredLines;
    std::vector<ROI> roiDataList;
    std::vector<LineCombination> lineCombinations;
    std::vector<EvaluationData> evalData;
    std::vector<EvaluationData> evalDataLeft;
    std::vector<EvaluationData> evalDataRight;

  public:
    LaneDetectionAlgorithm();
    ~LaneDetectionAlgorithm();

    void preProcessImage(cv::Mat &input);
    void getAllLine();
    void processDetectedLines(std::vector<cv::Vec4i> lines, bool draw = false);
    void processRawData(std::vector<std::vector<cv::Point2f>> &rois, bool debug,
                        bool draw);
    void processROIData(std::vector<std::vector<cv::Point2f>> &rois, bool debug,
                        bool draw);
    void filterDetLine(std::vector<DetLine> &detectedLines, bool draw);
    void generateLineCombo(std::vector<DetLine> &lines, int debug, bool draw);
    void evaluateLineCombo(std::vector<LineCombination> lineCombos,
                           std::vector<int> debug);
    void generateBestImage(int count);
    std::vector<cv::Mat> generateBestImageV(int count);
    cv::Mat generateComplexImage(int count, int hLimit);

    // new
    void generateEvalDataLeft(int choice);
    cv::Mat generateComplexImageLeft(int count, int hLimit);
    std::vector<cv::Mat> generateBestImageLeft(int count);

    // SETTERS
    void setImgGenCount(int count);
    void setSelectedEvalData(int v);

    // GETTERS
    int getImgGenCount();
    EvaluationData getEvalData();

    // static Method
    static bool isLineParallel(cv::Point2f p1, cv::Point2f p2, cv::Point2f p3,
                               cv::Point2f p4, double limit);
    static double getAngle(cv::Point2f p1, cv::Point2f p2);
    static cv::Point2f getIntersectionPoint(cv::Point2f p1, cv::Point2f p2,
                                            cv::Point2f p3, cv::Point2f p4);
    static double getAngleBetweenVector(cv::Point2f p1, cv::Point2f p2,
                                        cv::Point2f p3, cv::Point2f p4);
    static std::vector<cv::Point2f> getAllPointX(cv::Point2f &startPoint,
                                                 cv::Point2f &intersection);
    static std::vector<cv::Point2f> getAllPointY(cv::Point2f startPoint,
                                                 cv::Point2f intersection);
    double runEvaluation(LineCombination &l, std::vector<int> debug);

    // PROCESS
    void process(cv::Mat &input,
                 std::vector<std::vector<cv::Point2f>> &roiList);
};

#endif