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

#include <Algorithm/image_stabilizer/FeatureDetector.hpp>

/**
 * @brief FeatureDetector constructor
 *
 * @param type String indicating the type of detector to be used, such as "SIFT"
 * or "ORB".
 * @param imgMatches Boolean flag to determine whether to draw matches between
 * features in output or not.
 * @param imgFillOutput Boolean flag to determine whether to fill the output
 * image with matched features or not.
 */
FeatureDetector::FeatureDetector(std::string type, bool imgMatches,
                                 bool imgFillOutput)
    : detector_type_(type), drawMatches_(imgMatches),
      drawFillOutput_(imgFillOutput) {
    std::cout << "type: " << type << std::endl;
    if (detector_type_ == "SIFT") {
        std::cout << "SIFT" << std::endl;
        detector_ = cv::SIFT::create();
        // detector = cv::SIFT::create(100);

    } else {
        detector_ = cv::ORB::create(nfeatures, scaleFactor, nlevels,
                                    edgeThreshold, firstLevel, WTA_K, scoreType,
                                    patchSize, fastThreshold);
    }
}

/**
 * @overload FeatureDetector::FeatureDetector("SIFT", false, false)
 */
FeatureDetector::FeatureDetector() { FeatureDetector("SIFT", false, false); }

/**
 * @brief Runs the feature detection and matching algorithm on two input images.
 *
 * @param image1 First input image, Source Image.
 * @param image2 Second input image, Image to allign.
 */
void FeatureDetector::run(cv::Mat &image1, cv::Mat &image2) {
    FeatureDetector::clearVector();
    // TODO: run first compute at constructor/init
    detector_->detectAndCompute(image1, cv::Mat(), keyPoints1, descriptors1);
    detector_->detectAndCompute(image2, cv::Mat(), keyPoints2, descriptors2);

    DESCRIPTORMATCHER::FlannBasedMatcher(descriptors1, descriptors2, matchKP,
                                         "SIFT");
    DESCRIPTORMATCHER::FilterKeyPoints(matchKP, filterKP, 0.3);
    if (drawMatches_) {
        cv::drawMatches(image1, keyPoints1, image2, keyPoints2, filterKP,
                        siftResult, cv::Scalar::all(-1), cv::Scalar::all(-1),
                        std::vector<char>(),
                        cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    }

    HOMOGRAPHY::FindHomography(keyPoints1, keyPoints2, filterKP, obj, scene,
                               homographyMatrix, detector_type_);
    HOMOGRAPHY::PerscpectiveTransform(image2, transform, homographyMatrix);

    if (drawFillOutput_) {
        HOMOGRAPHY::FillTransform(image1, transform, homographyMatrix,
                                  fillOutput);
    }
}

/**
 * @brief Processes a vector of ImgData objects by running the feature detection
 * and matching algorithm on each pair of images.
 * This method processes the input images by running the feature
 * detection and matching algorithm on each pair of images in the vector. It
 * uses the first image in the vector as a reference to transform all subsequent
 * images to match its perspective. The transformed image is then stored in the
 * ImgData object and the process continues for the next pair of images.
 *
 * @param imgData A vector of ImgData objects that contains input images and
 * their metadata.
 */
void FeatureDetector::processImageData(std::vector<ImgData> &imgData) {
    cv::Mat firstImg = imgData.front().image;
    for (ImgData &img : imgData) {
        run(firstImg, img.image);
        img.image = transform.clone();
    }
}

/**
 * @brief Returns the result of Image Allignment filled with Background from
 * first Image.
 * @return A cv::Mat object that contains the result of Image Allignment filled
 * with Background from first Image.
 */
cv::Mat FeatureDetector::GetFillOutput() { return fillOutput; }

/**
 * @return A cv::Mat object that contains the transformed image obtained from
 * image allignment.
 * @brief Returns the transformed image obtained from image allignment.
 */
cv::Mat FeatureDetector::GetTransform() { return transform; }