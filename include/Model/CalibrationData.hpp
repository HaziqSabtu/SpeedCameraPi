#pragma once

#include "Utils/Struct/D_Line.hpp"

struct CalibData {
    Detection::Line lineLeft;
    Detection::Line lineRight;

    CalibData() {
        lineLeft = Detection::Line();
        lineRight = Detection::Line();
    }

    CalibData(Detection::Line lineLeft, Detection::Line lineRight) {
        this->lineLeft = lineLeft;
        this->lineRight = lineRight;
    }

    void clear() {
        lineLeft = Detection::Line();
        lineRight = Detection::Line();
    }

    bool isNull() { return lineLeft.isNull() || lineRight.isNull(); }
};