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

    void clear() {
        lineLeft = Line();
        lineRight = Line();
    }

    bool isNull() { return lineLeft.isNull() || lineRight.isNull(); }
};