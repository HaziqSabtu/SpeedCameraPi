#pragma once

#include <Algorithm/Struct/D_Line.hpp>
#include <Model/AllignData.hpp>

struct ResultData {
    ADVector allignData;
    std::vector<cv::Rect> trackedRoi;

    std::vector<double> speedList;
    std::vector<double> distanceFromCamera;
    std::vector<Line> intersectingLines;
    double speed = -1;

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
