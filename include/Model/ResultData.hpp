#pragma once

#include <Algorithm/Struct/D_Line.hpp>
#include <Model/AllignData.hpp>

/**
 * @brief Data for Result Process
 *
 */
struct ResultData {

    // The vector of AllignData
    ADVector allignData;

    // The vector of Rectangles / Tracked Objects
    std::vector<cv::Rect> trackedRoi;

    // Result of the Speed Calculation
    double speed = -1;

    // Value vor debugging
    std::vector<double> speedList;
    std::vector<double> distanceFromCamera;
    std::vector<Line> intersectingLines;

    ResultData();

    ResultData(std::vector<double> speedList,
               std::vector<double> distanceFromCamera,
               std::vector<Line> intersectingLines, double speed);

    bool isDefined();
    void clear();

    bool operator==(const ResultData &other) const;
    bool operator!=(const ResultData &other) const;
    ResultData clone() const;
    ResultData &operator=(const ResultData &other);
    void initAllignData(int size);
};
