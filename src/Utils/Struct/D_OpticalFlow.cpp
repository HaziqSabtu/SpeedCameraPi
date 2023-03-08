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
        data.push_back(Detection::OFPoint(i, points[i], 0, 1));
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
        data.push_back(
            Detection::OFPoint(OFData[i].id, points[i], errors[i], status[i]));
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
std::vector<cv::Point2f>
OpticalFlowData::GetPoints(std::vector<OFPoint> &points) {
    std::vector<cv::Point2f> p;
    for (int i = 0; i < points.size(); i++) {
        p.push_back(points[i].point);
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
    if (OFData.size() > data.size()) {
        throw "Size of OFData is bigger than data";
    }

    if (OFData.size() == data.size()) {
        return;
    }

    /**
     * * is this necessary? aren't data is always sorted?
     * * therefore normal iteration is enough maybe...
     * * but this is safer but with higher complexity
     *
     */
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

std::vector<Detection::OFPoint>
OpticalFlowData::threshold(OpticalFlowData &previous, float threshold) {
    std::vector<Detection::OFPoint> points;
    for (int i = 0; i < data.size(); i++) {
        Detection::OFPoint currP = data[i];
        Detection::OFPoint prevP = previous.GetPointById(currP.id);
        if (currP.status == 1 && prevP.status == 1 &&
            OFPoint::distance(currP, prevP) > threshold) {
            points.push_back(data[i]);
        }
    }
    return points;
}

Detection::OFPoint OpticalFlowData::GetPointById(int id) {
    auto p = find_if(
        data.begin(), data.end(),
        [id](const Detection::OFPoint &point) { return point.id == id; });

    if (p == data.end()) {
        throw std::runtime_error("No point found with id " +
                                 std::to_string(id));
    }

    return *p;
}

DetectionData::DetectionData() : points(std::vector<Detection::OFPoint>()) {}

DetectionData::DetectionData(std::vector<Detection::OFPoint> points)
    : points(points) {}

std::vector<cv::Point2f> DetectionData::GetPoints() {
    return OpticalFlowData::GetPoints(points);
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
