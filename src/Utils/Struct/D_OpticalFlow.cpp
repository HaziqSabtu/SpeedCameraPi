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

OFPoint::OFPoint(int id, cv::Point2f point, float error)
    : id(id), point(point), error(error) {}

OpticalFlowData::OpticalFlowData(cv::Mat gray)
    : gray(gray), data(std::vector<Detection::OFPoint>()) {}

OpticalFlowData::OpticalFlowData(cv::Mat gray, std::vector<cv::Point2f> points)
    : gray(gray) {
    data = std::vector<Detection::OFPoint>();
    push(points);
}

int OpticalFlowData::size() const { return data.size(); }

Detection::OFPoint &OpticalFlowData::operator[](int index) {
    return data[index];
}

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

std::vector<cv::Point2f> OpticalFlowData::GetPoint() {
    std::vector<cv::Point2f> points;
    for (int i = 0; i < data.size(); i++) {
        points.push_back(data[i].point);
    }
    return points;
}

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
