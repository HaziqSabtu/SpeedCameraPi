#include <Algorithm/speed_calculation/H_speedCalculation.hpp>

/**
 * @brief Construct a new Distance Speed Calculator:: Distance Speed Calculator
 * object
 *
 */
DistanceSpeedCalculator::DistanceSpeedCalculator() {}

/**
 * @brief Run the speed calculation
 *
 * @param images vector of captured images
 * @param times vector of captured times
 * @param trackedRoi vector of tracked roi
 * @param lines vector of lines representing the object start and end
 */
void DistanceSpeedCalculator::runCalculation(std::vector<cv::Mat> &images,
                                             std::vector<HPTime> &times,
                                             std::vector<cv::Rect> trackedRoi,
                                             std::vector<Line> &lines) {

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

/**
 * @brief Analyze the direction of the object. either moving upwards or
 * downwards
 *
 * @param trackedRoi vector of tracked roi
 */
void DistanceSpeedCalculator::analyzeDirection(
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

/**
 * @brief Assign the start and end lines based on the direction of the object
 *
 * @param lines vector of lines representing the object start and end
 */
void DistanceSpeedCalculator::assignLines(std::vector<Line> &lines) {
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

/**
 * @brief Check if the rect is crossing the line. Depends on direction of
 * movement
 *
 * @param line the Line object
 * @param rect the rect object
 * @return true if rect is crossing the line
 * @return false if rect is not crossing the line
 */
bool DistanceSpeedCalculator::isCrossingLine(Line &line, cv::Rect &rect) {
    cv::Point br = rect.br();

    if (direction == MOVING_DOWNWARDS) {
        return br.y > line.p1.y;
    } else {
        return br.y < line.p1.y;
    }
}

/**
 * @brief Return the speed of the object in m/s
 *
 * @return double speed in m/s
 */
double DistanceSpeedCalculator::GetSpeed() {
    if (isTimeDefault(startTime) || isTimeDefault(endTime)) {
        throw std::invalid_argument("Calculation not done yet");
    }

    if (objectLength <= 0) {
        throw std::invalid_argument("Object length must be greater than 0");
    }

    double timeDiff = Utils::TimeDiffInMilli(startTime, endTime);

    return objectLength / timeDiff;
}

/**
 * @brief Helper function to check if the time is default
 *
 * @param time the time to check
 * @return true if time is default (1st Jan 1970)
 * @return false if time is not default
 */
bool DistanceSpeedCalculator::isTimeDefault(HPTime &time) {
    return time == std::chrono::system_clock::from_time_t(0);
}

/**
 * @brief Set the object length in mm
 *
 * @param length the length of the object in mm
 */
void DistanceSpeedCalculator::setObjectLength(double length) {
    objectLength = length;
}

/**
 * @brief Get the object length in mm
 *
 * @return double the length of the object in mm
 */
double DistanceSpeedCalculator::getObjectLength() const { return objectLength; }

/**
 * @brief Get the type of speed calculation
 *
 * @return SpeedCalculationType the type of speed calculation
 */
SpeedCalculationType DistanceSpeedCalculator::GetType() const { return type; }
