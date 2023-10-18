#include <Model/ResultData.hpp>

ResultData::ResultData() {}

ResultData::ResultData(std::vector<double> speedList,
                       std::vector<double> distanceFromCamera,
                       std::vector<Line> intersectingLines, double speed)
    : speedList(speedList), distanceFromCamera(distanceFromCamera),
      intersectingLines(intersectingLines), speed(speed) {}

bool ResultData::isDefined() {
    if (speed == -1) {
        return false;
    }

    if (allignData.empty() || trackedRoi.empty()) {
        return false;
    }

    if (allignData.size() != trackedRoi.size()) {
        return false;
    }

    return true;
}

void ResultData::clear() {
    speed = -1;
    speedList.clear();
    distanceFromCamera.clear();
    intersectingLines.clear();
    allignData.clear();
    trackedRoi.clear();
}

bool ResultData::operator==(const ResultData &other) const {
    return speed == other.speed && speedList == other.speedList &&
           allignData == other.allignData && trackedRoi == other.trackedRoi &&
           distanceFromCamera == other.distanceFromCamera &&
           intersectingLines == other.intersectingLines;
}

bool ResultData::operator!=(const ResultData &other) const {
    return !(*this == other);
}

ResultData ResultData::clone() const { return ResultData(*this); }

ResultData &ResultData::operator=(const ResultData &other) {
    speed = other.speed;
    allignData = other.allignData;
    trackedRoi = other.trackedRoi;
    speedList = other.speedList;
    distanceFromCamera = other.distanceFromCamera;
    intersectingLines = other.intersectingLines;
    return *this;
}

void ResultData::initAllignData(int size) {
    if (size <= 0) {
        throw std::runtime_error("Size must be greater than 0");
    }

    allignData.resize(size);
}
