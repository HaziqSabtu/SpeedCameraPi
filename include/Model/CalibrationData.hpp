#pragma once

#include "Utils/Struct/D_Line.hpp"

struct CalibData {
    Line lineLeft;
    Line lineRight;

    CalibData() {
        lineLeft = Line();
        lineRight = Line();
    }

    CalibData(Line lineLeft, Line lineRight) {
        this->lineLeft = lineLeft;
        this->lineRight = lineRight;
    }

    void clear() {
        lineLeft = Line();
        lineRight = Line();
    }

    bool isNull() { return lineLeft.isNull() || lineRight.isNull(); }
};