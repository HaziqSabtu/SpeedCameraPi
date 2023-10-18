#pragma once

#include <Algorithm/Struct/D_Line.hpp>

struct CalibrationData {
    Line lineLeft;
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
