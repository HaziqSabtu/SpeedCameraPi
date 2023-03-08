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
OFPoint::OFPoint(int id, cv::Point2f point, float error, uchar status)
    : id(id), point(point), error(error), status(status) {}

/**
 * @brief Get the Distance between two Optical Flow Point
 *
 * @param p1 First Optical Flow Point
 * @param p2 Second Optical Flow Point
 * @return float distance
 */
float OFPoint::distance(OFPoint &p1, OFPoint &p2) {
    return cv::norm(p1.point - p2.point);
}

/**
 * @brief Construct a new Optical Flow Data:: Optical Flow Data object
 *
 */
OpticalFlowData::OpticalFlowData() {}
/**
 * @brief Construct a new Optical Flow Data:: Optical Flow Data object
 *
 * @param gray gray image
 */
OpticalFlowData::OpticalFlowData(cv::Mat gray)
    : gray(gray), data(std::unordered_map<int, Detection::OFPoint>()) {}

/**
 * @brief Construct a new Optical Flow Data:: Optical Flow Data object
 *
 * @param gray gray image
 * @param points vector of Optical Flow Point in cv::Point2f
 */
OpticalFlowData::OpticalFlowData(cv::Mat gray, std::vector<cv::Point2f> points)
    : gray(gray) {
    data = std::unordered_map<int, Detection::OFPoint>();
    push(points);
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
        data.insert({i, Detection::OFPoint(i, points[i], 0, 1)});
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
// TODO: Refractor again
void OpticalFlowData::push(OpticalFlowData &OFData,
                           std::vector<cv::Point2f> points,
                           std::vector<float> errors,
                           std::vector<uchar> status) {
    if (points.empty()) {
        throw "No points detected";
    }

    if (OFData.data.size() != points.size()) {
        throw "Size of points and OFData not match";
    }

    if (OFData.data.size() != status.size() || status.size() != errors.size()) {
        throw "Unmatched size of status and errors";
    }

    if (!data.empty()) {
        data.clear();
    }

    for (int i = 0; i < points.size(); i++) {
        data.insert(
            {i, Detection::OFPoint(i, points[i], errors[i], status[i])});
    }
}

std::vector<cv::Point2f> OpticalFlowData::GetPoints() {
    return GetPoints(data);
}

/**
 * @brief Convert Optical Flow Data to vector of Optical Flow Point
 *
 * @return std::vector<cv::Point2f>
 */
std::vector<cv::Point2f> OpticalFlowData::GetPoints(
    std::unordered_map<int, Detection::OFPoint> &points) {
    std::vector<cv::Point2f> p;
    for (int i = 0; i < points.size(); i++) {
        p.push_back(points.find(i)->second.point);
    }
    return p;
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
    if (OFData.data.size() > data.size()) {
        throw "Size of OFData is bigger than data";
    }

    if (OFData.data.size() == data.size()) {
        return;
    }

    /**
     * * is this necessary? aren't data is always sorted?
     * * therefore normal iteration is enough maybe...
     * * but this is safer but with higher complexity
     *
     */
    for (auto it = data.begin(); it != data.end();) {
        if (OFData.data.find(it->first) == OFData.data.end()) {
            it = data.erase(it);
        } else {
            it++;
        }
    }
}

std::vector<Detection::OFPoint>
OpticalFlowData::threshold(OpticalFlowData &previous, float threshold) {
    std::vector<Detection::OFPoint> points;
    for (auto it = data.begin(); it != data.end(); it++) {
        Detection::OFPoint currP = it->second;
        Detection::OFPoint prevP = previous.GetPointById(it->first);
        if (currP.id != prevP.id) {
            std::cout << "ID not match" << std::endl;
        }
        if (currP.status == 1 && prevP.status == 1 &&
            OFPoint::distance(currP, prevP) > threshold) {
            points.push_back(currP);
        }
    }
    return points;
}

Detection::OFPoint OpticalFlowData::GetPointById(int id) {
    return data.find(id)->second;
}

DetectionData::DetectionData() : points(std::vector<Detection::OFPoint>()) {}

DetectionData::DetectionData(std::vector<Detection::OFPoint> points)
    : points(points) {}

std::vector<cv::Point2f> DetectionData::GetPoints() {
    std::vector<cv::Point2f> p;
    for (int i = 0; i < points.size(); i++) {
        p.push_back(points[i].point);
    }
    return p;
}

cv::Rect DetectionData::GetRect() { return cv::boundingRect(GetPoints()); }

Detection::Line DetectionData::GetLine() {
    std::vector<cv::Point2f> p = GetPoints();
    std::sort(p.begin(), p.end(),
              [](cv::Point2f &a, cv::Point2f &b) { return a.y > b.y; });
    cv::Point2f selected = p.front();
    return Detection::Line(selected, cv::Point2f(selected.x + 1, selected.y));
}

} // namespace Detection
