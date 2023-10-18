#include <Model/CalibrationData.hpp>

CalibrationData::CalibrationData() {
    lineLeft = Line();
    lineRight = Line();
}

CalibrationData::CalibrationData(Line lineLeft, Line lineRight) {
    this->lineLeft = lineLeft;
    this->lineRight = lineRight;
}

bool CalibrationData::operator==(const CalibrationData &other) const {
    return lineLeft == other.lineLeft && lineRight == other.lineRight;
}

bool CalibrationData::operator!=(const CalibrationData &other) const {
    return !(*this == other);
}

void CalibrationData::clear() {
    lineLeft = Line();
    lineRight = Line();
}

bool CalibrationData::isNull() {
    return lineLeft.isNull() || lineRight.isNull();
}

CalibrationData CalibrationData::clone() const {
    return CalibrationData(*this);
}

CalibrationData &CalibrationData::operator=(const CalibrationData &other) {
    lineLeft = other.lineLeft.clone();
    lineRight = other.lineRight.clone();
    return *this;
}
