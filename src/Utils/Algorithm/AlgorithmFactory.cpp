#include <Utils/Algorithm/AlgorithmFactory.hpp>

/**
 * @brief Create Pointer to HSVFilter object
 *
 * @param config AppConfig object
 * @return HSVFilterPtr
 */
HSVFilterPtr AlgorithmFactory::createHSVFilter(AppConfig &config) {
    return std::make_shared<HSVFilter>();
}

/**
 * @brief Create Pointer BFS object
 *
 * @param config AppConfig object
 * @return BFSPtr
 */
BFSPtr AlgorithmFactory::createBFS(AppConfig &config) {
    return std::make_shared<BFS>();
}

/**
 * @brief Create Pointer to FeatureDetector object
 *
 * @param config AppConfig object
 * @return DetectorPtr
 */
DetectorPtr AlgorithmFactory::createFeatureDetector(AppConfig &config) {
    return std::make_shared<FeatureDetector>(DetectorType::SIFT);
}

/**
 * @brief Create Pointer to OFTracker object
 *
 * @param config AppConfig object
 * @return OFTrackerPtr
 */
OFTrackerPtr AlgorithmFactory::createOFTracker(AppConfig &config) {
    auto OFConfig = config.GetOpticalFlowConfig();

    auto tracker = std::make_shared<OFTracker>();
    tracker->SetMaxCorners(OFConfig.maxCorners);
    tracker->SetQualityLevel(OFConfig.qualityLevel);
    tracker->SetMinDistance(OFConfig.minDistance);
    tracker->SetBlockSize(OFConfig.blockSize);
    tracker->SetUseHarrisDetector(OFConfig.useHarrisDetector);
    tracker->SetK(OFConfig.k);
    tracker->SetMinPointDistance(OFConfig.minPointDistance);
    tracker->SetThreshold(OFConfig.threshold);
    return tracker;
}

/**
 * @brief Create Pointer to CSRTTracker object
 *
 * @param config AppConfig object
 * @return CSRTTrackerPtr
 */
CSRTTrackerPtr AlgorithmFactory::createCSRTTracker(AppConfig &config) {
    return std::make_shared<CSRTTracker>();
}

/**
 * @brief Create Pointer to RansacLine object
 *
 * @param config AppConfig object
 * @return RansacLinePtr
 */
RansacLinePtr AlgorithmFactory::createRansacLine(AppConfig &config) {
    auto RansacConfig = config.GetRansacConfig();
    int minPoints = RansacConfig.minPoints;
    int maxIterations = RansacConfig.maxIterations;
    double threshold = RansacConfig.threshold;
    return std::make_shared<RansacLine>(maxIterations, minPoints, threshold);
}

/**
 * @brief Create Pointer to LaneSpeedCalculator object
 *
 * @param config AppConfig object
 * @return LaneCalcPtr
 */
LaneCalcPtr AlgorithmFactory::createLaneSpeedCalculator(AppConfig &config) {
    auto sConfig = config.GetSensorConfig();
    auto mConfig = config.GetMeasurementConfig();

    auto speedCalc = std::make_shared<LaneSpeedCalculator>();
    speedCalc->SetSensorWidth(sConfig.SensorWidth);
    speedCalc->SetFocalLength(sConfig.SensorFocalLength);
    speedCalc->SetLaneWidth(mConfig.ObjectWidth);
    return speedCalc;
}

/**
 * @brief Create Pointer to DistanceSpeedCalculator object
 *
 * @param config AppConfig object
 * @return DistanceCalcPtr
 */
DistanceCalcPtr
AlgorithmFactory::createDistanceSpeedCalculator(AppConfig &config) {
    auto mConfig = config.GetMeasurementConfig();

    auto speedCalc = std::make_shared<DistanceSpeedCalculator>();
    speedCalc->setObjectLength(mConfig.ObjectHeight);
    return speedCalc;
}