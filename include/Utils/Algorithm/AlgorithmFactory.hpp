#pragma once

#include <Algorithm/hsv_filter/BFS.hpp>
#include <Algorithm/hsv_filter/HSVFilter.hpp>
#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <Algorithm/object_tracker/CSRTTracker.hpp>
#include <Algorithm/object_tracker/OpticalFlowTracker.hpp>
#include <Algorithm/ransac_line/RansacLine.hpp>
#include <Algorithm/speed_calculation/H_speedCalculation.hpp>
#include <Algorithm/speed_calculation/speedCalculation.hpp>

#include <Utils/Config/AppConfig.hpp>

#include <memory>

#define AF AlgorithmFactory

#define HSVFilterPtr std::shared_ptr<HSVFilter>
#define BFSPtr std::shared_ptr<BFS>
#define DetectorPtr std::shared_ptr<FeatureDetector>
#define OFTrackerPtr std::shared_ptr<OFTracker>
#define CSRTTrackerPtr std::shared_ptr<CSRTTracker>
#define RansacLinePtr std::shared_ptr<RansacLine>
#define SpeedCalcPtr std::shared_ptr<SpeedCalculator>
#define LaneCalcPtr std::shared_ptr<LaneSpeedCalculator>
#define DistanceCalcPtr std::shared_ptr<DistanceSpeedCalculator>

class AlgorithmFactory {
  public:
    static HSVFilterPtr createHSVFilter(AppConfig &config);

    static BFSPtr createBFS(AppConfig &config);

    static DetectorPtr createFeatureDetector(AppConfig &config);

    static OFTrackerPtr createOFTracker(AppConfig &config);
    static CSRTTrackerPtr createCSRTTracker(AppConfig &config);

    static RansacLinePtr createRansacLine(AppConfig &config);

    static LaneCalcPtr createLaneSpeedCalculator(AppConfig &config);
    static DistanceCalcPtr createDistanceSpeedCalculator(AppConfig &config);
};