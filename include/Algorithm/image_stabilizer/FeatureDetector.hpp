#ifndef FeatureDetector_HPP
#define FeatureDetector_HPP

#include <Algorithm/image_stabilizer/DescriptorMatcher.hpp>
#include <Algorithm/image_stabilizer/Homography.hpp>
#include <Utils/fileWR.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

class FeatureDetector {

  public:
    FeatureDetector(std::string type, bool imgMatches = false,
                    bool imgFillOutput = false);
    void run(cv::Mat &image1, cv::Mat &image2);
    void processImageData(std::vector<ImgData> &imgData);
    cv::Mat GetFillOutput();
    cv::Mat GetTransform();

  private:
    cv::Ptr<cv::Feature2D> detector_;
    std::string detector_type_;
    bool drawMatches_;
    bool drawFillOutput_;
    void clearVector();

    // ORB Parameters
    int nfeatures = 2000;
    float scaleFactor = 1.2f;
    int nlevels = 8;
    int edgeThreshold = 31;
    int firstLevel = 0;
    int WTA_K = 2;
    int patchSize = 31;
    int fastThreshold = 20;
    cv::ORB::ScoreType scoreType = cv::ORB::HARRIS_SCORE;

  private:
    cv::Mat descriptors1;
    cv::Mat descriptors2;
    cv::Mat siftResult;
    cv::Mat homographyMatrix;
    cv::Mat transform;
    cv::Mat fillOutput;

    std::vector<cv::KeyPoint> keyPoints1;
    std::vector<cv::KeyPoint> keyPoints2;

    std::vector<cv::Point2f> obj;
    std::vector<cv::Point2f> scene;

    std::vector<cv::DMatch> filterKP;
    std::vector<std::vector<cv::DMatch>> matchKP;
};

inline void FeatureDetector::clearVector() {
    filterKP.clear();
    matchKP.clear();
    obj.clear();
    scene.clear();
    keyPoints1.clear();
    keyPoints2.clear();
}

#endif