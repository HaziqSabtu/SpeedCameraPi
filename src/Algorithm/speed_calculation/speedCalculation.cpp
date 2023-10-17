/**
 * @file speedCalculation.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Calculating Speed of Object from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Model/SessionData.hpp"
#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <cmath>
#include <iostream>
#include <vector>

LaneSpeedCalculator::LaneSpeedCalculator() {}

void LaneSpeedCalculator::runCalculation(std::vector<cv::Mat> &images,
                                         std::vector<HPTime> &times,
                                         std::vector<cv::Rect> trackedRoi,
                                         std::vector<Line> &lines) {
    if (lines.size() != 2) {
        throw std::invalid_argument("Lines size must be 2");
        return;
    }

    if (images.size() == 0) {
        throw std::invalid_argument("Images size must be greater than 0");
        return;
    }

    imageWidth = images.at(0).cols;

    for (int i = 0; i < images.size(); i++) {

        cv::Rect roi = trackedRoi.at(i);
        cv::Point br = roi.br();
        cv::Point bl = roi.br() - cv::Point(roi.width, 0);

        auto botL = Line(br, bl).Extrapolate(images.at(i));

        cv::Point2f intersection1 = botL.Intersection(lines[0]);
        cv::Point2f intersection2 = botL.Intersection(lines[1]);

        double pixelDist = fabs(intersection1.x - intersection2.x);

        double dist1 = distanceFromCameraInMilli(pixelDist);

        HPTime currTime = times.at(i);

        if (prevDistFromCamera != -1) {
            double speed =
                calculateSpeed(prevDistFromCamera, dist1, prevTime, currTime);
            speeds.push_back(speed);
        }

        prevDistFromCamera = dist1;
        prevTime = currTime;

        distFromCamera.push_back(dist1);
        intersectingLines.push_back(Line(intersection1, intersection2));
    }
}

/**
 * @brief Calculate Object Distance from Camera
 *
 * @param pixelWidth Width of the object in pixels
 * @return double   Distance of the object from the camera in mm
 */
double LaneSpeedCalculator::distanceFromCameraInMilli(float pixelWidth) {
    return (laneWidth * imageWidth * focalLength) / (pixelWidth * sensorWidth);
}

/**
 * @brief Calculate the average speed from a vector of speeds
 *
 * @param speeds vector of speeds
 * @return double average speed
 */
double LaneSpeedCalculator::GetRawAverageSpeed() {
    if (speeds.size() == 0) {
        return -1;
    }

    double sum = 0;
    for (double speed : speeds) {
        sum += speed;
    }
    return sum / speeds.size();
}

/**
 * @brief Calculate the speed of the object
 *
 * @param prevDist previous distance of the object from the camera
 * @param curDist current distance of the object from the camera
 * @param prevTime previous time of frame
 * @param curTime current time of frame
 * @return double speed of the object
 */
double LaneSpeedCalculator::calculateSpeed(double prevDist, double curDist,
                                           HPTime prevTime, HPTime curTime) {
    double distDiff = fabs(curDist - prevDist);
    double timeDiff = Utils::TimeDiffInMilli(prevTime, curTime);

    return distDiff / timeDiff;
}

double LaneSpeedCalculator::GetSpeed() {
    if (speeds.size() == 0) {
        throw std::invalid_argument("Speeds size must be greater than 0");
    }

    return Utils::TrimmedMean(speeds, trimPercentage);
}

double LaneSpeedCalculator::GetSensorWidth() const { return this->sensorWidth; }

void LaneSpeedCalculator::SetSensorWidth(double width) {
    this->sensorWidth = width;
}

double LaneSpeedCalculator::GetFocalLength() const { return this->focalLength; }

void LaneSpeedCalculator::SetFocalLength(double length) {
    this->focalLength = length;
}

double LaneSpeedCalculator::GetLaneWidth() const { return this->laneWidth; }

void LaneSpeedCalculator::SetLaneWidth(double width) {
    this->laneWidth = width;
}

std::vector<double> LaneSpeedCalculator::GetDistanceFromCamera() const {
    return distFromCamera;
}

std::vector<Line> LaneSpeedCalculator::GetIntersectingLines() const {
    return intersectingLines;
}

std::vector<double> LaneSpeedCalculator::GetRawSpeed() const { return speeds; }

SpeedCalculationType LaneSpeedCalculator::GetType() const { return type; }