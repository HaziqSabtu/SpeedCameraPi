#include "SIFTDetection.hpp"

SIFTDetection::SIFTDetection(/* args */) { detector = cv::SIFT::create(); }

SIFTDetection::~SIFTDetection() {}

void SIFTDetection::run(cv::Mat &image1, cv::Mat &image2) {
    clearVector();
    detector->detectAndCompute(image1, cv::Mat(), keyPoints1, descriptors1);
    detector->detectAndCompute(image2, cv::Mat(), keyPoints2, descriptors2);

    DESCRIPTORMATCHER::FlannBasedMatcher(descriptors1, descriptors2, matchKP,
                                         "SIFT");
    DESCRIPTORMATCHER::FilterKeyPoints(matchKP, filterKP, 0.3);

    drawMatches(image1, keyPoints1, image2, keyPoints2, filterKP, siftResult,
                cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(),
                cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    HOMOGRAPHY::FindHomography(keyPoints1, keyPoints2, filterKP, obj, scene,
                               homographyMatrix, "SIFT");
    HOMOGRAPHY::PerscpectiveTransform(image2, transform, homographyMatrix);
    HOMOGRAPHY::FillTransform(image1, transform, homographyMatrix, fillOutput);
}

void SIFTDetection::processImageData(std::vector<ImgData> &imgData) {
    cv::Mat firstImg = imgData.front().image;
    for (ImgData &img : imgData) {
        run(firstImg, img.image);
        img.image = transform.clone();
    }
}

void SIFTDetection::clearVector() {
    filterKP.clear();
    matchKP.clear();
    obj.clear();
    scene.clear();
    keyPoints1.clear();
    keyPoints2.clear();
}

cv::Mat SIFTDetection::getFillOutput() { return fillOutput; }
cv::Mat SIFTDetection::getTransform() { return transform; }
