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
 * @brief Runs the feature detection and matching algorithm on two input images.
 *
 * @details
 * <ul>
 * <li> 1. Detect and compute features on both images.
 * <li> 2. Match features between the two images.
 * <li> 3. Filter the matched features.
 * <li> 4. Find homography matrix.
 * <li> 5. Apply homography matrix to the second image.
 * </ul>
 *
 * @param image1 First input image, Source Image.
 * @param image2 Second input image, Image to allign.
 */
void FeatureDetector::allign(cv::Mat &image1, cv::Mat &image2) {
    // TODO: run first compute at constructor/init
    FeatureDetector::clearVector();
    std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
    detector->detectAndCompute(image1, cv::Mat(), keyPoints1, descriptors1);

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    detector->detectAndCompute(image2, cv::Mat(), keyPoints2, descriptors2);

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    DMatcher::FlannBasedMatcher(descriptors1, descriptors2, matchKP,
                                detectorType);

    std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
    DMatcher::FilterKeyPoints(matchKP, filterKP, 0.3);

    std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();
    homographyMatrix =
        Homography::FindHomography(keyPoints1, keyPoints2, filterKP);

    std::chrono::steady_clock::time_point t5 = std::chrono::steady_clock::now();
    transform = Homography::PerscpectiveTransform(image2, homographyMatrix);
    std::chrono::steady_clock::time_point t6 = std::chrono::steady_clock::now();

    std::cout << "Init1: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                     .count()
              << " ms" << std::endl;

    std::cout << "Init2: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << " ms" << std::endl;

    std::cout << "Flann MAtcher: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2)
                     .count()
              << " ms" << std::endl;

    std::cout << "Filter KP: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3)
                     .count()
              << " ms" << std::endl;
    std::cout << "Find Homography: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4)
                     .count()
              << " ms" << std::endl;

    std::cout << "Transform: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5)
                     .count()
              << " ms" << std::endl;

    std::cout << "Total: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t0)
                     .count()
              << " ms" << std::endl;
}

/**
 * @brief Run image allignment on a vector of ImageData objects.
 * Attention! The result will replace the original image in the ImageData
 * object.
 *
 * @param imgData result of Image Allignment.
 */
void FeatureDetector::allign(std::vector<ImageData> &imgData) {
    cv::Mat firstImg = imgData.front().image;
    for (ImageData &img : imgData) {
        allign(firstImg, img.image);
        img.image = transform.clone();
    }
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