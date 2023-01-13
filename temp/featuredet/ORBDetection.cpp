#include "ORBDetection.hpp"

ORBDetection::ORBDetection(/* args */) {
    detector =
        cv::ORB::create(nfeatures, scaleFactor, nlevels, edgeThreshold,
                        firstLevel, WTA_K, scoreType, patchSize, fastThreshold);
}

ORBDetection::~ORBDetection() {}

void ORBDetection::run(cv::Mat &image1, cv::Mat &image2) {
    detector->detectAndCompute(image1, cv::Mat(), keyPoints1, descriptors1);
    detector->detectAndCompute(image2, cv::Mat(), keyPoints2, descriptors2);

    DESCRIPTORMATCHER::FlannBasedMatcher(descriptors1, descriptors2, matchKP,
                                         "ORB");
    DESCRIPTORMATCHER::FilterKeyPoints(matchKP, filterKP, 0.3);

    drawMatches(image1, keyPoints1, image2, keyPoints2, filterKP, siftResult);

    HOMOGRAPHY::FindHomography(keyPoints1, keyPoints2, filterKP, obj, scene,
                               homographyMatrix, "ORB");
    HOMOGRAPHY::PerscpectiveTransform(image2, transform, homographyMatrix);
    HOMOGRAPHY::FillTransform(image1, transform, homographyMatrix, fillOutput);

    imshow("ORB RESULT", siftResult);
    imshow("ORB Transform", transform);
    imshow("ORB Transform2", fillOutput);
}
