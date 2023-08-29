/**
 * @file DescriptorMatcher.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief A class for performing feature matching using OpenCV's
 * DMatcher class.
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Algorithm/image_allign/DescriptorMatcher.hpp>

/**
 * @brief Perform brute-force matching between query and target descriptors
 * using OpenCV's BFMatcher class.
 *
 * method uses the provided `query` and `target` descriptors to perform
 * brute-force matching using OpenCV's `BFMatcher` class. The resulting matches
 * are stored in the `matches` vector. The `type` parameter specifies the type
 * of descriptors being used (e.g., "ORB", "SIFT", etc.), while the `normType`
 * parameter specifies the type of distance metric to use (e.g., `cv::NORM_L2`,
 * `cv::NORM_HAMMING`, etc.).
 *
 * @param query The query descriptors to match against.
 * @param target The target descriptors to match with.
 * @param matches The resulting matches between query and target descriptors.
 * @param type The type of descriptors being used.
 * @param normType The type of distance metric to use (default = 0).
 */
void DMatcher::BruteForceMatcher(cv::Mat &query, cv::Mat &target,
                                 std::vector<cv::DMatch> &matches,
                                 std::string type, int normType) {
    // Only For ORB ?
    cv::NormTypes normTypes;
    std::string typeName;

    getNormType(normType, normTypes, typeName);

    // crosscheck is True for Normal Matching
    cv::BFMatcher matcher(normTypes, true);
    std::cout << "Running BruteForce with " << typeName << std::endl;

    matcher.match(query, target, matches);
}

// TODO: DOCS
void DMatcher::BruteForceMatcher(cv::Mat &query, cv::Mat &target,
                                 std::vector<std::vector<cv::DMatch>> &matches,
                                 std::string type, int normType) {
    // Only For ORB ?
    cv::NormTypes normTypes;
    std::string typeName;

    getNormType(normType, normTypes, typeName);

    cv::BFMatcher matcher(normTypes, false);
    std::cout << "Running BruteForce + KNN  with " << typeName << std::endl;
    matcher.knnMatch(query, target, matches, 2);
}

// TODO: DOCS -> Use Enum
/**
 * @brief Map an integer `normType` value to a corresponding `cv::NormTypes`
 * enum value and string type name.
 *
 * This method takes an integer `normType` value and maps it to the
 * corresponding `cv::NormTypes` enum value and string type name. The resulting
 * `normTypes` and `typeName` values are passed by reference. The `normType`
 * parameter should be an integer between 0 and 8, inclusive, where each value
 * corresponds to a specific type of distance metric.
 *
 * @param normType The integer norm type value to map to a `cv::NormTypes` enum
 * value and string type name.
 * @param normTypes The resulting `cv::NormTypes` enum value.
 * @param typeName The resulting string type name.
 */
void DMatcher::getNormType(int normType, cv::NormTypes &normTypes,
                           std::string &typeName) {
    switch (normType) {
        case 0:
            normTypes = cv::NORM_HAMMING;
            typeName = "NORM_HAMMING";
            break;
        case 1:
            normTypes = cv::NORM_INF;
            typeName = "NORM_INF";
            break;
        case 2:
            normTypes = cv::NORM_L1;
            typeName = "NORM_L1";
            break;
        case 3:
            normTypes = cv::NORM_L2;
            typeName = "NORM_L2";
            break;
        case 4:
            normTypes = cv::NORM_L2SQR;
            typeName = "NORM_L2SQR";
            break;
        case 5:
            normTypes = cv::NORM_HAMMING2;
            typeName = "NORM_HAMMING2";
            break;
        case 6:
            normTypes = cv::NORM_TYPE_MASK;
            typeName = "NORM_TYPE_MASK";
            break;
        case 7:
            normTypes = cv::NORM_RELATIVE;
            typeName = "NORM_RELATIVE";
            break;
        case 8:
            normTypes = cv::NORM_MINMAX;
            typeName = "NORM_MINMAX";
            break;
    }
}

/**
 * @brief Match feature descriptors in query and target images using the
 * FLANN-based matcher.
 *
 * This method matches feature descriptors in the query and target images using
 * the FLANN-based matcher, which is a fast approximate nearest neighbor search
 * algorithm. The resulting matches are stored in the `matches` vector, where
 * each element of the vector is a vector of `cv::DMatch` objects representing
 * the matches between the query and target descriptors.
 *
 * @param query The query image feature descriptors.
 * @param target The target image feature descriptors.
 * @param matches The resulting vector of vector of matches.
 * @param type The type of feature detector used to generate the descriptors.
 */
void DMatcher::FlannBasedMatcher(cv::Mat &query, cv::Mat &target,
                                 std::vector<std::vector<cv::DMatch>> &matches,
                                 DetectorType type) {

    if (type == DetectorType::SIFT) {
        cv::Ptr<cv::DescriptorMatcher> matcher =
            cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
        matcher->knnMatch(query, target, matches, 2);
    } else {
        throw std::logic_error("Feature detector not implemented yet");
    }
}

/**
 * @brief Filters keypoint matches using Lowe's Ratio Test.
 * @param knnMatches Input vector of k-nearest-neighbor matches between query
 * and target keypoints.
 * @param goodMatch Output vector of filtered matches.
 * @param RATIO Threshold ratio for the distances of the first and second
 * nearest neighbors to consider a match good.
 */
void DMatcher::FilterKeyPoints(std::vector<std::vector<cv::DMatch>> &knnMatches,
                               std::vector<cv::DMatch> &goodMatch,
                               double RATIO) {
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i].size() >= 2) {
            if (knnMatches[i][0].distance < knnMatches[i][1].distance * 0.3)
                goodMatch.push_back(knnMatches[i][0]);
        }
    }
    std::cout << "Filtered KeyPoints: " << goodMatch.size() << std::endl;
}