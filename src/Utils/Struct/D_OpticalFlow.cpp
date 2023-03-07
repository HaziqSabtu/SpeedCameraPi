/**
 * @file D_OpticalFlow.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Struct for Optical Flow Data
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Utils/Struct/D_OpticalFlow.hpp>

namespace Detection {

/**
 * @brief Construct a new OFPoint::OFPoint object
 *
 * @param id unique id for each point
 * @param point Optical Flow Point in cv::Point2f
 * @param error error of Optical Flow Point
 */
OFPoint::OFPoint(int id, cv::Point2f point, float error)
    : id(id), point(point), error(error) {}

/**
 * @brief Construct a new Optical Flow Data:: Optical Flow Data object
 *
 * @param gray gray image
 */
OpticalFlowData::OpticalFlowData(cv::Mat gray)
    : gray(gray), data(std::vector<Detection::OFPoint>()) {}

/**
 * @brief Construct a new Optical Flow Data:: Optical Flow Data object
 *
 * @param gray gray image
 * @param points vector of Optical Flow Point in cv::Point2f
 */
OpticalFlowData::OpticalFlowData(cv::Mat gray, std::vector<cv::Point2f> points)
    : gray(gray) {
    data = std::vector<Detection::OFPoint>();
    push(points);
}

/**
 * @brief Get the Size of Optical Flow Data
 *
 * @return int data size
 */
int OpticalFlowData::size() const { return data.size(); }

/**
 * @brief Get the Optical Flow Point at index
 *
 * @param index index of Optical Flow Point
 * @return Detection::OFPoint& Optical Flow Point
 */
Detection::OFPoint &OpticalFlowData::operator[](int index) {
    return data[index];
}

/**
 * @brief Push Optical Flow Point to Optical Flow Data
 * @details This is default push function for Optical Flow Data. Therefore all
 * error is set to 0.
 *
 * @param points vector of Optical Flow Point in cv::Point2f
 * @throw "No points detected" if points is empty
 */
void OpticalFlowData::push(std::vector<cv::Point2f> points) {
    if (points.empty()) {
        throw "No points detected";
    }

    if (!data.empty()) {
        data.clear();
    }
    for (int i = 0; i < points.size(); i++) {
        data.push_back(Detection::OFPoint(i, points[i], 0));
    }
}

/**
 * @brief Push Optical Flow Point to Optical Flow Data
 * @details This is push function for Optical Flow Data with error.
 * While pushing, the Optical Flow Point will be filtered by status of previous
 * OpticalFlowData. If status is 1, the Optical Flow Point will be pushed to
 * Optical Flow Data.
 *
 * @param OFData Optical Flow Data to compare
 * @param points vector of Optical Flow Point in cv::Point2f
 * @param errors vector of error of Optical Flow Point
 * @param status vector of status of Optical Flow Point
 * @throw "No points detected" if points is empty
 * @throw "Size of points and OFData not match" if size of points and OFData not
 */
void OpticalFlowData::push(OpticalFlowData OFData,
                           std::vector<cv::Point2f> points,
                           std::vector<float> errors,
                           std::vector<uchar> status) {
    if (points.empty()) {
        throw "No points detected";
    }

    if (OFData.data.size() != points.size()) {
        throw "Size of points and OFData not match";
    }

    if (!data.empty()) {
        data.clear();
    }

    for (int i = 0; i < points.size(); i++) {
        if (status[i] == 1) {
            data.push_back(
                Detection::OFPoint(OFData[i].id, points[i], errors[i]));
        }
    }
}

/**
 * @brief Convert Optical Flow Data to vector of Optical Flow Point
 *
 * @return std::vector<cv::Point2f>
 */
std::vector<cv::Point2f> OpticalFlowData::GetPoint() {
    std::vector<cv::Point2f> points;
    for (int i = 0; i < data.size(); i++) {
        points.push_back(data[i].point);
    }
    return points;
}

/**
 * @brief Update current Point Data
 * @details This function will update current Optical Flow Data with new
 * Optical Flow Data. This function will remove all Optical Flow Point that is
 * not in new Optical Flow Data.
 *
 * @param OFData new Optical Flow Data
 */
void OpticalFlowData::update(OpticalFlowData OFData) {
    if (OFData.size() > data.size()) {
        throw "Size of OFData is bigger than data";
    }

    if (OFData.size() == data.size()) {
        return;
    }

    // is this necessary?
    // arent data is always sorted?
    // therefore normal iteration is enough
    // maybe...
    // but this is safer
    // but with higher complexity
    data.erase(remove_if(data.begin(), data.end(),
                         [&OFData](Detection::OFPoint &point) {
                             return find_if(OFData.data.begin(),
                                            OFData.data.end(),
                                            [&point](Detection::OFPoint &p) {
                                                return p.id == point.id;
                                            }) == OFData.data.end();
                         }),
               data.end());
}

} // namespace Detection
