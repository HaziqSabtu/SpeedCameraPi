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
#include <Algorithm/object_tracker/OpticalFlowData.hpp>

/**
 * @brief Construct a new OFPoint::OFPoint object
 *
 * @param id unique id for each point
 * @param point Optical Flow Point in cv::Point2f
 * @param error error of Optical Flow Point
 * @param status status of Optical Flow Point
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
 * @brief Construct a new Detection Data:: Detection Data object
 *
 */
DetectionData::DetectionData() : points(std::vector<OFPoint>()) {}

/**
 * @brief Construct a new Detection Data:: Detection Data object
 *
 * @param points vector of Optical Flow Point
 */
DetectionData::DetectionData(std::vector<OFPoint> points) : points(points) {}

/**
 * @brief Get Optical Flow Point from Detection Data
 *
 * @return std::vector<cv::Point2f>
 */
std::vector<cv::Point2f> DetectionData::GetPoints() {
    std::vector<cv::Point2f> p;
    for (int i = 0; i < points.size(); i++) {
        p.push_back(points[i].point);
    }
    return p;
}

/**
 * @brief Get Bounding Box from Detection Data
 *
 * @return cv::Rect
 */
cv::Rect DetectionData::GetRect() { return cv::boundingRect(GetPoints()); }

/**
 * @brief Get Line of the Point that located at the bottom of the Bounding Box
 *
 * @return Line
 */
Line DetectionData::GetLine() {
    std::vector<cv::Point2f> p = GetPoints();
    std::sort(p.begin(), p.end(),
              [](cv::Point2f &a, cv::Point2f &b) { return a.y > b.y; });
    cv::Point2f selected = p.front();
    return Line(selected, cv::Point2f(selected.x + 1, selected.y));
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
    : gray(gray), data(std::unordered_map<int, OFPoint>()) {}

/**
 * @brief Construct a new Optical Flow Data:: Optical Flow Data object
 *
 * @param gray gray image
 * @param points vector of Optical Flow Point in cv::Point2f
 */
OpticalFlowData::OpticalFlowData(cv::Mat gray, std::vector<cv::Point2f> points)
    : gray(gray) {
    data = std::unordered_map<int, OFPoint>();
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
        data.insert({i, OFPoint(i, points[i], 0, 1)});
    }
}

/**
 * @brief Push Optical Flow Point to Optical Flow Data
 *
 * @param OFData Optical Flow Data to compare
 * @param points vector of Optical Flow Point in cv::Point2f
 * @param errors vector of error of Optical Flow Point
 * @param status vector of status of Optical Flow Point
 * @throw "No points detected" if points is empty
 * @throw "Size of points and OFData not match" if size of points and OFData not
 */
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
        data.insert({i, OFPoint(i, points[i], errors[i], status[i])});
    }
}

/**
 * @brief Get Optical Flow Point from Optical Flow Data
 *
 * @return std::vector<cv::Point2f>
 */
std::vector<cv::Point2f> OpticalFlowData::GetPoints() {
    return GetPoints(data);
}

/**
 * @brief Convert Optical Flow Data to vector of Optical Flow Point
 *
 * @return std::vector<cv::Point2f>
 */
std::vector<cv::Point2f>
OpticalFlowData::GetPoints(std::unordered_map<int, OFPoint> &points) {
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

    for (auto it = data.begin(); it != data.end();) {
        if (OFData.data.find(it->first) == OFData.data.end()) {
            it = data.erase(it);
        } else {
            it++;
        }
    }
}

/**
 * @brief Apply threshold to Optical Flow Data
 * @details This function will remove all Optical Flow Point that is not in
 * threshold
 * <ul>
 * <li> Iterate through all Optical Flow Point in Optical Flow Data
 * <li> Compare Optical Flow Point with Optical Flow Point in previous Optical
 * Flow Data
 * <li> If the distance between Optical Flow Point and Optical Flow Point in
 * previous Optical Flow Data is bigger than threshold, remove it
 * </ul>
 * @note deprecated ?
 * @param previous previous OpticalFlowData
 * @param threshold threshold
 * @return std::vector<OFPoint> vector of Optical Flow Point that
 * pass threshold
 */
std::vector<OFPoint> OpticalFlowData::threshold(OpticalFlowData &previous,
                                                float threshold) {
    std::vector<OFPoint> points;
    for (auto it = data.begin(); it != data.end(); it++) {
        OFPoint currP = it->second;
        OFPoint prevP = previous.GetPointById(it->first);
        if (currP.status == 1 && prevP.status == 1 &&
            OFPoint::distance(currP, prevP) > threshold) {
            points.push_back(currP);
        }
    }
    return points;
}

/**
 * @brief Apply threshold to Optical Flow Data
 * @details This function will remove all Optical Flow Point that is not in
 * threshold
 * <ul>
 * <li> Iterate through all Optical Flow Point in Optical Flow Data
 * <li> Compare Optical Flow Point with Optical Flow Point in previous Optical
 * Flow Data
 * <li> If the distance between Optical Flow Point and Optical Flow Point in
 * previous Optical Flow Data is bigger than threshold, remove it
 * </ul>
 * @param ids vector of id
 * @param previous previous OpticalFlowData
 * @param threshold threshold
 */
void OpticalFlowData::thresholdPointsId(std::vector<int> &ids,
                                        OpticalFlowData &previous,
                                        float threshold) {
    for (int id : ids) {
        OFPoint currP = GetPointById(id);
        OFPoint prevP = previous.GetPointById(id);
        if (currP.status != 1 || prevP.status != 1 ||
            OFPoint::distance(currP, prevP) < threshold) {
            ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
        }
    }
}

/**
 * @brief Get Optical Flow Point by ids
 *
 * @param ids vector of id
 * @return std::vector<OFPoint>
 */
std::vector<OFPoint> OpticalFlowData::GetPointsById(std::vector<int> &ids) {
    std::vector<OFPoint> points;
    for (int id : ids) {
        points.push_back(GetPointById(id));
    }
    return points;
}

/**
 * @brief Get Optical Flow Point by id
 *
 * @param id id
 * @return OFPoint
 */
OFPoint OpticalFlowData::GetPointById(int id) { return data.find(id)->second; }
