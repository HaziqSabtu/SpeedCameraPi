#include <Algorithm/image_stabilizer/DescriptorMatcher.hpp>

void DESCRIPTORMATCHER::BruteForceMatcher(cv::Mat &query, cv::Mat &target,
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

void DESCRIPTORMATCHER::BruteForceMatcher(
    cv::Mat &query, cv::Mat &target,
    std::vector<std::vector<cv::DMatch>> &matches, std::string type,
    int normType) {
    // Only For ORB ?
    cv::NormTypes normTypes;
    std::string typeName;

    getNormType(normType, normTypes, typeName);

    cv::BFMatcher matcher(normTypes, false);
    std::cout << "Running BruteForce + KNN  with " << typeName << std::endl;
    matcher.knnMatch(query, target, matches, 2);
}

void DESCRIPTORMATCHER::getNormType(int normType, cv::NormTypes &normTypes,
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

void DESCRIPTORMATCHER::FlannBasedMatcher(
    cv::Mat &query, cv::Mat &target,
    std::vector<std::vector<cv::DMatch>> &matches, std::string type) {
    if (type == "ORB") {
        std::cout << "Running FlannBasedMatcher with ORB" << std::endl;
        cv::FlannBasedMatcher matcher = cv::FlannBasedMatcher(
            cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2));
        matcher.knnMatch(query, target, matches, 2);
    } else if (type == "SIFT") {
        cv::Ptr<cv::DescriptorMatcher> matcher =
            cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
        matcher->knnMatch(query, target, matches, 2);
    }
}

// Run Lowe's Ratio Test to remove bad matches on KNN.
void DESCRIPTORMATCHER::FilterKeyPoints(
    std::vector<std::vector<cv::DMatch>> &knnMatches,
    std::vector<cv::DMatch> &goodMatch, double RATIO) {
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i].size() >= 2) {
            if (knnMatches[i][0].distance < knnMatches[i][1].distance * 0.3)
                goodMatch.push_back(knnMatches[i][0]);
        }
    }
    std::cout << "Filtered KeyPoints: " << goodMatch.size() << std::endl;
}