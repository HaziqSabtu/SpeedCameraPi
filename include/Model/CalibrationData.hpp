#pragma once

#include "Algorithm/Struct/D_Line.hpp"

struct CalibrationData {
    Line lineLeft;
    Line lineRight;

    CalibrationData() {
        lineLeft = Line();
        lineRight = Line();
    }

    CalibrationData(Line lineLeft, Line lineRight) {
        this->lineLeft = lineLeft;
        this->lineRight = lineRight;
    }

    bool operator==(const CalibrationData &other) const {
        return lineLeft == other.lineLeft && lineRight == other.lineRight;
    }

    bool operator!=(const CalibrationData &other) const {
        return !(*this == other);
    }

    void clear() {
        lineLeft = Line();
        lineRight = Line();
    }

    bool isNull() { return lineLeft.isNull() || lineRight.isNull(); }

    CalibrationData clone() const { return CalibrationData(*this); }

    CalibrationData &operator=(const CalibrationData &other) {
        lineLeft = other.lineLeft.clone();
        lineRight = other.lineRight.clone();
        return *this;
    }
};