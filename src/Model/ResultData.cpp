#include <Model/ResultData.hpp>

/**
 * @brief Construct a new ResultData:: ResultData object
 *
 */
ResultData::ResultData() {}

ResultData::ResultData(std::vector<double> speedList,
                       std::vector<double> distanceFromCamera,
                       std::vector<Line> intersectingLines, double speed)
    : speedList(speedList), distanceFromCamera(distanceFromCamera),
      intersectingLines(intersectingLines), speed(speed) {}

/**
 * @brief Check if the ResultData is defined
 *
 * @return true if defined
 * @return false if not defined
 */
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

/**
 * @brief Clear the ResultData
 *
 */
void ResultData::clear() {
    speed = -1;
    speedList.clear();
    distanceFromCamera.clear();
    intersectingLines.clear();
    allignData.clear();
    trackedRoi.clear();
}

/**
 * @brief Equal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool ResultData::operator==(const ResultData &other) const {
    return speed == other.speed && speedList == other.speedList &&
           allignData == other.allignData && trackedRoi == other.trackedRoi &&
           distanceFromCamera == other.distanceFromCamera &&
           intersectingLines == other.intersectingLines;
}

/**
 * @brief Unequal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool ResultData::operator!=(const ResultData &other) const {
    return !(*this == other);
}

/**
 * @brief Clone this ResultData
 *
 * @return ResultData
 */
ResultData ResultData::clone() const { return ResultData(*this); }

/**
 * @brief Copy Assignment Operator
 *
 * @param other
 * @return ResultData&
 */
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
