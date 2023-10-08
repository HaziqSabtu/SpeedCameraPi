#include <Algorithm/speed_calculation/H_speedCalculation.hpp>

HorizontalSpeedCalculation::HorizontalSpeedCalculation() {}

void HorizontalSpeedCalculation::runCalculation(
    std::vector<cv::Mat> &images, std::vector<HPTime> &times,
    std::vector<cv::Rect> trackedRoi, std::vector<Line> &lines) {

    if (lines.size() != 2) {
        throw std::invalid_argument("Lines size must be 2");
    }

    if (images.size() == 0) {
        throw std::invalid_argument("Images size must be greater than 0");
    }

    if (trackedRoi.size() != images.size() ||
        trackedRoi.size() != times.size()) {
        throw std::invalid_argument("Invalid input size");
    }

    analyzeDirection(trackedRoi);

    assignLines(lines);

    for (int i = 0; i < images.size(); i++) {
        cv::Rect roi = trackedRoi.at(i);
        cv::Point br = roi.br();

        if (isTimeDefault(startTime) && isCrossingLine(startLine, roi)) {
            startTime = times.at(i);
        }

        if (isTimeDefault(endTime) && isCrossingLine(endLine, roi)) {
            endTime = times.at(i);
        }
    }

    if (isTimeDefault(startTime) || isTimeDefault(endTime)) {
        throw std::invalid_argument("Calculation error - start or end time not "
                                    "found");
    }
}

void HorizontalSpeedCalculation::analyzeDirection(
    std::vector<cv::Rect> &trackedRoi) {
    auto firstRectBrPoint = trackedRoi.front().br();
    auto lastRectBrPoint = trackedRoi.back().br();

    if (firstRectBrPoint.y == lastRectBrPoint.y) {
        throw std::invalid_argument("First and last rect cannot be on same "
                                    "horizontal line");
    }

    if (firstRectBrPoint.y > lastRectBrPoint.y) {
        direction = MOVING_UPWARDS;
    } else {
        direction = MOVING_DOWNWARDS;
    }
}

void HorizontalSpeedCalculation::assignLines(std::vector<Line> &lines) {
    Line lowerLine;
    Line upperLine;

    // assume both lines are horizontal
    // compare y values of both lines
    if (lines[0].p1.y > lines[1].p1.y) {
        lowerLine = lines[0];
        upperLine = lines[1];
    } else {
        lowerLine = lines[1];
        upperLine = lines[0];
    }

    if (direction == MOVING_DOWNWARDS) {
        startLine = upperLine;
        endLine = lowerLine;
    } else {
        startLine = lowerLine;
        endLine = upperLine;
    }
}

bool HorizontalSpeedCalculation::isCrossingLine(Line &line, cv::Rect &rect) {
    cv::Point br = rect.br();

    if (direction == MOVING_DOWNWARDS) {
        return br.y > line.p1.y;
    } else {
        return br.y < line.p1.y;
    }
}

// return in m/s
double HorizontalSpeedCalculation::GetSpeed() {
    if (isTimeDefault(startTime) || isTimeDefault(endTime)) {
        throw std::invalid_argument("Calculation not done yet");
    }

    if (objectLength <= 0) {
        throw std::invalid_argument("Object length must be greater than 0");
    }

    double timeDiff = Utils::TimeDiffInMilli(startTime, endTime);

    return objectLength / timeDiff;
}

bool HorizontalSpeedCalculation::isTimeDefault(HPTime &time) {
    return time == std::chrono::system_clock::from_time_t(0);
}

void HorizontalSpeedCalculation::setObjectLength(double length) {
    objectLength = length;
}

double HorizontalSpeedCalculation::getObjectLength() const {
    return objectLength;
}
