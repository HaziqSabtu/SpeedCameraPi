/**
 * @file FeatureDetector.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for detecting and matching features between two images and
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <opencv2/core/types.hpp>

/**
 * @brief FeatureDetector constructor
 *
 * @param type Feature type from DetectorType to be used for feature detection.
 */
FeatureDetector::FeatureDetector(DetectorType type) : detectorType(type) {
    if (detectorType == DetectorType::SIFT) {
        detector = cv::SIFT::create();
    } else {
        throw std::logic_error("ORB not implemented yet");
    }
}

/**
 * @overload FeatureDetector::FeatureDetector("SIFT", false, false)
 */
FeatureDetector::FeatureDetector() : FeatureDetector(DetectorType::SIFT) {}

/**
 * @brief Copy constructor
 *
 * @param other FeatureDetector object to be copied.
 */
FeatureDetector &FeatureDetector::operator=(const FeatureDetector &other) {
    if (this != &other) {
        this->detectorType = other.detectorType;
        this->detector = other.detector;
        this->keyPoints1 = other.keyPoints1;
        this->keyPoints2 = other.keyPoints2;
        this->descriptors1 = other.descriptors1.clone();
        this->descriptors2 = other.descriptors2.clone();
        this->homographyMatrix = other.homographyMatrix.clone();
        this->transform = other.transform.clone();
    }
    return *this;
}

/**
 * @brief Clone function
 *
 * @return FeatureDetector
 */
FeatureDetector FeatureDetector::clone() { return FeatureDetector(*this); }

void FeatureDetector::Init(cv::Mat &image1) {
    clearVector();

    if (image1.empty()) {
        throw std::logic_error("Image is empty");
    }

    detector->detectAndCompute(image1, cv::Mat(), keyPoints1, descriptors1);
}

void FeatureDetector::Allign(cv::Mat &image2) {
    if (image2.empty()) {
        throw std::logic_error("Image is empty");
    }

    if (keyPoints1.empty() || descriptors1.empty()) {
        throw std::logic_error("No keypoints detected. Run Init() first.");
    }

    if (keyPoints2.empty() || descriptors2.empty()) {
        keyPoints2.clear();
        descriptors2.release();
    }

    detector->detectAndCompute(image2, cv::Mat(), keyPoints2, descriptors2);

    DMatcher::FlannBasedMatcher(descriptors1, descriptors2, matchKP,
                                detectorType);

    DMatcher::FilterKeyPoints(matchKP, filterKP, 0.3);

    homographyMatrix =
        Homography::FindHomography(keyPoints1, keyPoints2, filterKP);

    transform = Homography::PerscpectiveTransform(image2, homographyMatrix);
}

/**
 * @brief Returns the image with the keypoints drawn on it.
 *
 * @param image1 Source image.
 * @param image2 Target image.
 * @return cv::Mat Image with keypoints drawn on it.
 */
cv::Mat FeatureDetector::GetMatchImage(cv::Mat &image1, cv::Mat &image2) {
    if (keyPoints1.empty() || keyPoints2.empty()) {
        throw std::logic_error("No keypoints detected. Run allign() first.");
    }
    cv::Mat result;
    cv::drawMatches(image1, keyPoints1, image2, keyPoints2, filterKP, result,
                    cv::Scalar::all(-1), cv::Scalar::all(-1),
                    std::vector<char>(),
                    cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    return result;
}

/**
 * @brief Inline function to clear all vectors from previous run
 *
 */
void FeatureDetector::clearVector() {
    filterKP.clear();
    matchKP.clear();
    keyPoints1.clear();
    keyPoints2.clear();
}

/**
 * @brief Returns the homography matrix used to transform the second image to
 * match the perspective of the first image.
 *
 * @return cv::Mat Homography matrix.
 */
cv::Mat FeatureDetector::GetHomographyMatrix() { return homographyMatrix; }

/**
 * @brief Returns the transformed image.
 *
 * @return cv::Mat Transformed image.
 */
cv::Mat FeatureDetector::GetAllignedImage() { return transform; }

/**
 * @brief Returns the image with the transformed image pasted on top of the
 * first image or background.
 *
 * @param bg Background image.
 * @return cv::Mat result image.
 */
cv::Mat FeatureDetector::GetAllignedImage(cv::Mat &bg) {
    return Homography::FillTransform(bg, transform, homographyMatrix);
}