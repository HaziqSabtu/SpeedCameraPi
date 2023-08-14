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

/**
 * @brief Construct a new Speed Calculation:: Speed Calculation object
 *
 * @param sensorWidth Width of the sensor in mm
 * @param sensorFocalLength Focal Length of the sensor in mm
 * @param objectWidth Width of the object in mm
 */
SpeedCalculation::SpeedCalculation(const double sensorWidth,
                                   const double sensorFocalLength,
                                   const double objectWidth)
    : SensorWidth(sensorWidth), FocalLength(sensorFocalLength),
      LANE_WIDTH(objectWidth) {}

/**
 * @brief Run Speed Calculation
 * @details this method is not recommended to use. SpeedData will be removed in
 * the future. Use the other runCalculation method instead
 * @param speedData
 */
void SpeedCalculation::runCalculation(std::vector<SpeedData> speedData) {
    if (line.size() != 2) {
        std::cout << "Line Size Error" << std::endl;
        return;
    }

    if (speedData.size() == 0) {
        std::cout << "No data" << std::endl;
        return;
    }

    speeds.clear();
    int i = 0;
    for (SpeedData data : speedData) {

        cv::Point2f bottom = data.BottomLine();
        cv::Point2f intersection1 = intersection(bottom.y, line[0]);
        cv::Point2f intersection2 = intersection(bottom.y, line[1]);

        double pixelDist = fabs(intersection1.x - intersection2.x);
        double dist1 = distanceFromCamera(pixelDist);

        std::cout << "####################" << std::endl;
        std::cout << i << ": Distance: " << dist1 << std::endl;

        if (prevDistFromCamera != -1) {
            double speed =
                calcSpeed(prevDistFromCamera, dist1, prevTime, data.time);

            std::cout << "Speed: " << speed << std::endl;
            speeds.push_back(speed);
        }

        prevDistFromCamera = dist1;
        prevTime = data.time;
        i++;
    }

    double rawSpeed = rawAvgSpeed(speeds);
    avgSpeed = Utils::TrimmedMean(speeds, 10);
    // this section is for testing only
    // will be removed in the future
    // TODO: remove this section
    double measuredSpeed = 0.3 / 1.2;

    std::cout << "Measured Speed: " << measuredSpeed << std::endl;
    std::cout << "average Speed: " << avgSpeed << std::endl;

    double error = fabs(avgSpeed - measuredSpeed) * 100 / measuredSpeed;

    std::cout << "Error: " << error << std::endl;

    std::cout << "Raw Speed: " << rawSpeed << std::endl;
}

/**
 * @brief Run Speed Calculation
 * @details preferred method to use
 * @param imgData ImageData to be used for calculation
 * @param lines Selected Lines
 */
void SpeedCalculation::runCalculation(std::vector<ImageData> *imgData,
                                      std::vector<Detection::Line> &lines) {
    throw std::runtime_error("Not implemented");
    // if (lines.size() != 2) {
    //     std::cout << "Line Size Error" << std::endl;
    //     return;
    // }

    // if (images.size() == 0) {
    //     std::cout << "No data" << std::endl;
    //     return;
    // }
    // std::cout << "images.size(): " << images.size() << std::endl;
    // for (int i = 1; i < images.size(); i++) {

    //     std::cout << "i: " << i << std::endl;
    //     Detection::Line botL = imgData->at(i).detection.GetLine();

    //     std::cout << "botL: " << botL.ToString() << std::endl;
    //     cv::Point2f intersection1 = botL.Intersection(lines[0]);
    //     cv::Point2f intersection2 = botL.Intersection(lines[1]);

    //     std::cout << "intersection1: " << intersection1 << std::endl;
    //     std::cout << "intersection2: " << intersection2 << std::endl;

    //     double pixelDist = fabs(intersection1.x - intersection2.x);

    //     std::cout << "pixelDist: " << pixelDist << std::endl;
    //     double dist1 = distanceFromCamera(pixelDist);

    //     std::cout << "####################" << std::endl;
    //     std::cout << i << ": Distance: " << dist1 << std::endl;

    //     std::chrono::high_resolution_clock::time_point currTime =
    //         imgData->at(i).time;

    //     if (prevDistFromCamera != -1) {

    //         double speed =
    //             calcSpeed(prevDistFromCamera, dist1, prevTime, currTime);

    //         std::cout << "Speed: " << speed << std::endl;
    //         speeds.push_back(speed);
    //     }

    //     prevDistFromCamera = dist1;
    //     prevTime = currTime;
    // }

    // double rawSpeed = rawAvgSpeed(speeds);
    // avgSpeed = Utils::TrimmedMean(speeds, 20);

    // // this section is for testing only
    // // will be removed in the future
    // // TODO: remove this section

    // double measuredSpeed = 0.3 / 1.2;

    // std::cout << "Measured Speed: " << measuredSpeed << std::endl;
    // std::cout << "average Speed: " << avgSpeed << std::endl;

    // double error = fabs(avgSpeed - measuredSpeed) * 100 / measuredSpeed;

    // std::cout << "Error: " << error << std::endl;

    // std::cout << "Raw Speed: " << rawSpeed << std::endl;
}

void SpeedCalculation::runCalculation2(std::vector<cv::Mat> &images,
                                       std::vector<HPTime> &times,
                                       std::vector<cv::Rect> trackedRoi,
                                       std::vector<Detection::Line> &lines) {
    if (lines.size() != 2) {
        std::cout << "Line Size Error" << std::endl;
        return;
    }

    if (images.size() == 0) {
        std::cout << "No data" << std::endl;
        return;
    }
    std::cout << "images.size(): " << images.size() << std::endl;
    for (int i = 1; i < images.size(); i++) {

        std::cout << "i: " << i << std::endl;
        cv::Rect roi = trackedRoi.at(i);
        cv::Point botPoint = roi.br();
        cv::Point botPoint2 = roi.br() - cv::Point(roi.width, 0);

        std::cerr << "botPoint: " << botPoint << std::endl;
        std::cerr << "botPoint2: " << botPoint2 << std::endl;

        auto botL =
            Detection::Line(botPoint, botPoint2).Extrapolate(images.at(i));
        // Detection::Line botL = imgData->at(i).detection.GetLine();

        std::cout << "botL: " << botL.ToString() << std::endl;
        cv::Point2f intersection1 = botL.Intersection(lines[0]);
        cv::Point2f intersection2 = botL.Intersection(lines[1]);

        std::cout << "intersection1: " << intersection1 << std::endl;
        std::cout << "intersection2: " << intersection2 << std::endl;

        double pixelDist = fabs(intersection1.x - intersection2.x);

        std::cout << "pixelDist: " << pixelDist << std::endl;
        double dist1 = distanceFromCamera(pixelDist);

        std::cout << "####################" << std::endl;
        std::cout << i << ": Distance: " << dist1 << std::endl;

        std::chrono::high_resolution_clock::time_point currTime = times.at(i);

        if (prevDistFromCamera != -1) {

            double speed =
                calcSpeed(prevDistFromCamera, dist1, prevTime, currTime);

            std::cerr << "Speed: " << speed << std::endl;
            speeds.push_back(speed);
        }

        prevDistFromCamera = dist1;
        prevTime = currTime;
    }

    double rawSpeed = rawAvgSpeed(speeds);
    avgSpeed = Utils::TrimmedMean(speeds, 20);

    // // this section is for testing only
    // // will be removed in the future
    // // TODO: remove this section

    // double measuredSpeed = 0.3 / 1.2;

    // std::cout << "Measured Speed: " << measuredSpeed << std::endl;
    // std::cout << "average Speed: " << avgSpeed << std::endl;

    // double error = fabs(avgSpeed - measuredSpeed) * 100 / measuredSpeed;

    // std::cout << "Error: " << error << std::endl;

    // std::cout << "Raw Speed: " << rawSpeed << std::endl;
}

/**
 * @brief Calculate Object Distance from Camera
 *
 * @param pixelWidth Width of the object in pixels
 * @return double   Distance of the object from the camera in mm
 */
double SpeedCalculation::distanceFromCamera(float pixelWidth) {
    return (LANE_WIDTH * imageWidth * FocalLength) / (pixelWidth * SensorWidth);
}

/**
 * @brief Set the Selected Line to be used for calculation
 * @details This method is not recommended to use. SpeedData will be removed in
 * the future. The selected Lines should be passed to the runCalculation method
 * instead
 *
 * @param l
 */
void SpeedCalculation::SetLine(std::vector<cv::Vec4i> l) { line = l; }

/**
 * @brief Set the Image Width to be used for calculation
 *
 * @param w width of the image
 */
void SpeedCalculation::SetImageWidth(int w) { this->imageWidth = w; }

/**
 * @brief Convert ImageData to SpeedData
 * @details This method is not recommended to use. SpeedData will be removed in
 * the future.
 * @param imgData ImageData to be converted
 * @param points Points to be used for calculation
 * @return std::vector<SpeedData>
 */
std::vector<SpeedData>
SpeedCalculation::toSpeedData(std::vector<ImageData> &imgData,
                              std::vector<std::vector<cv::Point2f>> &points) {
    std::vector<SpeedData> speedData;
    for (int i = 0; i < imgData.size(); i++) {
        SpeedData data;
        data.image = imgData[i].image;
        data.time = imgData[i].time;
        data.points = points[i];
        speedData.push_back(data);
    }
    return speedData;
}

/**
 * @brief Calculate the intersection point of two lines
 * @details Overloaded method
 *
 * @param y
 * @param b
 * @return cv::Point2f
 */
cv::Point2f SpeedCalculation::intersection(float y, cv::Vec4i b) {
    cv::Vec4f b2(b[0], b[1], b[2], b[3]);
    cv::Vec4f a(0, y, 1, y);
    return intersection(a, b2);
}

/**
 * @brief Calculate the intersection point of two lines
 *
 * @param a First line in the form of cv::Vec4f
 * @param b Second line in the form of cv::Vec4f
 * @return cv::Point2f Intersection point in the form of cv::Point2f
 */
cv::Point2f SpeedCalculation::intersection(cv::Vec4f a, cv::Vec4f b) {
    cv::Point2f p;
    float x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
    float x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0) {
        return cv::Point2f(-1, -1);
    }
    p.x =
        ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
    p.y =
        ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;
    return p;
}

/**
 * @brief Calculate the average speed from a vector of speeds
 *
 * @param speeds vector of speeds
 * @return double average speed
 */
double SpeedCalculation::rawAvgSpeed(std::vector<double> &speeds) {
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
double SpeedCalculation::calcSpeed(
    double prevDist, double curDist,
    std::chrono::high_resolution_clock::time_point prevTime,
    std::chrono::high_resolution_clock::time_point curTime) {
    double distDiff = fabs(curDist - prevDist);
    double timeDiff = Utils::TimeDiff(prevTime, curTime);

    std::cout << "DistDiff: " << distDiff << std::endl;
    std::cout << "TimeDiff: " << timeDiff << std::endl;
    return distDiff / timeDiff;
}

/**
 * @brief Get the Average calculated speed
 *
 * @return double average speed
 */
double SpeedCalculation::GetAvgSpeed() { return avgSpeed; }