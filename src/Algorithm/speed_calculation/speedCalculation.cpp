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
#include <iostream>
#include <vector>

SpeedCalculation::SpeedCalculation() {}

void SpeedCalculation::runCalculation(std::vector<cv::Mat> &images,
                                      std::vector<HPTime> &times,
                                      std::vector<cv::Rect> trackedRoi,
                                      std::vector<Detection::Line> &lines) {
    if (lines.size() != 2) {
        throw std::invalid_argument("Lines size must be 2");
        return;
    }

    if (images.size() == 0) {
        throw std::invalid_argument("Images size must be greater than 0");
        return;
    }

    imageWidth = images.at(0).cols;

    for (int i = 1; i < images.size(); i++) {

        cv::Rect roi = trackedRoi.at(i);
        cv::Point br = roi.br();
        cv::Point bl = roi.br() - cv::Point(roi.width, 0);

        auto botL = Detection::Line(br, bl).Extrapolate(images.at(i));

        cv::Point2f intersection1 = botL.Intersection(lines[0]);
        cv::Point2f intersection2 = botL.Intersection(lines[1]);

        double pixelDist = fabs(intersection1.x - intersection2.x);

        double dist1 = distanceFromCameraInMilli(pixelDist);

        std::chrono::high_resolution_clock::time_point currTime = times.at(i);

        if (prevDistFromCamera != -1) {
            double speed =
                calculateSpeed(prevDistFromCamera, dist1, prevTime, currTime);
            speeds.push_back(speed);
        }

        prevDistFromCamera = dist1;
        prevTime = currTime;
    }
}

/**
 * @brief Calculate Object Distance from Camera
 *
 * @param pixelWidth Width of the object in pixels
 * @return double   Distance of the object from the camera in mm
 */
double SpeedCalculation::distanceFromCameraInMilli(float pixelWidth) {
    return (laneWidth * imageWidth * focalLength) / (pixelWidth * sensorWidth);
}

/**
 * @brief Calculate the average speed from a vector of speeds
 *
 * @param speeds vector of speeds
 * @return double average speed
 */
double SpeedCalculation::GetRawAverageSpeed() {
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
double SpeedCalculation::calculateSpeed(double prevDist, double curDist,
                                        HPTime prevTime, HPTime curTime) {
    double distDiff = fabs(curDist - prevDist);
    double timeDiff = Utils::TimeDiff(prevTime, curTime);

    return distDiff / timeDiff;
}

double SpeedCalculation::GetTrimmedAverageSpeed(int percentage) {
    if (speeds.size() == 0) {
        return -1;
    }

    return Utils::TrimmedMean(speeds, percentage);
}

double SpeedCalculation::GetSensorWidth() const { return this->sensorWidth; }

void SpeedCalculation::SetSensorWidth(double width) {
    this->sensorWidth = width;
}

double SpeedCalculation::GetFocalLength() const { return this->focalLength; }

void SpeedCalculation::SetFocalLength(double length) {
    this->focalLength = length;
}

double SpeedCalculation::GetLaneWidth() const { return this->laneWidth; }

void SpeedCalculation::SetLaneWidth(double width) { this->laneWidth = width; }

std::vector<double> SpeedCalculation::GetRawSpeed() const { return speeds; }