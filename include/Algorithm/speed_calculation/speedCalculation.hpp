/**
 * @file speedCalculation.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class for Calculating Speed of Object from Image using Optical Flow
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SPEED_CALCULATION_HPP
#define SPEED_CALCULATION_HPP

#include "Model/SessionData.hpp"
#include <Algorithm/Struct/D_Line.hpp>
#include <Utils/CommonUtils.hpp>
#include <chrono>
#include <opencv2/core.hpp>

/**
 * @brief Enum for speed calculation type
 *
 */
enum SpeedCalculationType {
    SPEED_CALCULATION_LANE,
    SPEED_CALCULATION_DISTANCE,
};

/**
 * @brief The abstract base class for speed calculation algorithms.
 * @details This class is used to calculate the speed of an object in a video.
 * It is an abstract base class, and must be inherited by a derived class.
 * Subclass of SpeedCalculator must implement the runCalculation() method, which
 * takes a vector of images, a vector of time points, a vector of rectangles
 * representing the tracked region of interest (ROI), and a vector of lines used
 * for speed calculation. The subclass must also implement the GetSpeed()
 * method, which returns the calculated speed.
 */
class SpeedCalculator {
  public:
    /**
     * @brief Default constructor.
     */
    SpeedCalculator() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~SpeedCalculator() = default;

    /**
     * @brief Run the speed calculation.
     *
     * @param images A vector of images representing the video frames.
     * @param times A vector of time points corresponding to the frames.
     * @param trackedRoi A vector of rectangles representing the tracked region
     * of interest (ROI).
     * @param lines A vector of lines used for speed calculation.
     */
    virtual void runCalculation(std::vector<cv::Mat> &images,
                                std::vector<HPTime> &times,
                                std::vector<cv::Rect> trackedRoi,
                                std::vector<Line> &lines) = 0;

    /**
     * @brief Get the calculated speed.
     *
     * @return The calculated speed.
     */
    virtual double GetSpeed() = 0;

    /**
     * @brief Get the type of speed calculation algorithm.
     *
     * @return The type of speed calculation.
     */
    virtual SpeedCalculationType GetType() const = 0;
};

/**
 * @brief Class for Calculating Speed with Lane Width (Pinhole Camera Model)
 *
 */
class LaneSpeedCalculator : public SpeedCalculator {
  public:
    LaneSpeedCalculator();

    void runCalculation(std::vector<cv::Mat> &images,
                        std::vector<HPTime> &times,
                        std::vector<cv::Rect> trackedRoi,
                        std::vector<Line> &lines);

    double GetSpeed();

    SpeedCalculationType GetType() const;

    double GetRawAverageSpeed();
    std::vector<double> GetRawSpeed() const;

    double GetSensorWidth() const;
    void SetSensorWidth(double width);

    double GetFocalLength() const;
    void SetFocalLength(double length);

    double GetLaneWidth() const;
    void SetLaneWidth(double width);

    std::vector<double> GetDistanceFromCamera() const;
    std::vector<Line> GetIntersectingLines() const;

  private:
    double distanceFromCameraInMilli(float pixelWidth);

    double calculateSpeed(double prevDist, double curDist, HPTime prevTime,
                          HPTime curTime);

  private:
    const SpeedCalculationType type = SPEED_CALCULATION_LANE;

    int imageWidth;
    double sensorWidth = 3.68; // in mm
    double focalLength = 3.04; // in mm
    double laneWidth = 3500;   // in mm

    // set default values for prevTime -1
    double prevDistFromCamera = -1;
    HPTime prevTime;

    int trimPercentage = 20;

    std::vector<double> speeds;

    // debugging data
    std::vector<double> distFromCamera;
    std::vector<Line> intersectingLines;
};

#endif