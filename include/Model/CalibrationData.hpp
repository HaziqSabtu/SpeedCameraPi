#pragma once

#include <Algorithm/Struct/D_Line.hpp>

/**
 * @brief Data for Calibration
 * @note The left and right Line, does not actually have to be left and right,
 * can be any two lines
 *
 */
struct CalibrationData {
    // The left Line
    Line lineLeft;

    // The right Line
    Line lineRight;

    CalibrationData();
    CalibrationData(Line lineLeft, Line lineRight);

    bool operator==(const CalibrationData &other) const;
    bool operator!=(const CalibrationData &other) const;
    void clear();
    bool isNull();
    CalibrationData clone() const;
    CalibrationData &operator=(const CalibrationData &other);
};
