#include <Model/CalibrationData.hpp>

/**
 * @brief Construct a new CalibrationData:: CalibrationData object
 *
 */
CalibrationData::CalibrationData() {
    lineLeft = Line();
    lineRight = Line();
}

/**
 * @brief Construct a new CalibrationData:: CalibrationData object
 *
 * @param lineLeft The Line 1
 * @param lineRight The Line 2
 */
CalibrationData::CalibrationData(Line lineLeft, Line lineRight) {
    this->lineLeft = lineLeft;
    this->lineRight = lineRight;
}

/**
 * @brief Equal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool CalibrationData::operator==(const CalibrationData &other) const {
    return lineLeft == other.lineLeft && lineRight == other.lineRight;
}

/**
 * @brief Unequal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool CalibrationData::operator!=(const CalibrationData &other) const {
    return !(*this == other);
}

/**
 * @brief Clear the CalibrationData
 *
 */
void CalibrationData::clear() {
    lineLeft = Line();
    lineRight = Line();
}

/**
 * @brief Check if the CalibrationData is Null
 *
 * @return true
 * @return false
 */
bool CalibrationData::isNull() {
    return lineLeft.isNull() || lineRight.isNull();
}

/**
 * @brief Clone the CalibrationData
 *
 * @return CalibrationData
 */
CalibrationData CalibrationData::clone() const {
    return CalibrationData(*this);
}

/**
 * @brief Copy Assignment Operator
 *
 * @param other
 * @return CalibrationData&
 */
CalibrationData &CalibrationData::operator=(const CalibrationData &other) {
    lineLeft = other.lineLeft.clone();
    lineRight = other.lineRight.clone();
    return *this;
}
