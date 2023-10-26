#include <Model/TrackingData.hpp>

/**
 * @brief Construct a new TrackingData:: TrackingData object
 *
 */
TrackingData::TrackingData() {}

/**
 * @brief Construct a new TrackingData:: TrackingData object
 *
 * @param roi The initial ROI
 */
TrackingData::TrackingData(cv::Rect roi) : roi(roi) {}

/**
 * @brief Clear the TrackingData
 *
 */
void TrackingData::clear() { roi = cv::Rect(); }

/**
 * @brief Check if the TrackingData is initialized
 *
 * @return true if initialized
 * @return false if not initialized
 */
bool TrackingData::isInit() { return roi.area() > 0; }

/**
 * @brief Equal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool TrackingData::operator==(const TrackingData &other) const {
    return roi == other.roi;
}

/**
 * @brief Not Equal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool TrackingData::operator!=(const TrackingData &other) const {
    return !(*this == other);
}

/**
 * @brief Clone the TrackingData
 *
 * @return TrackingData
 */
TrackingData TrackingData::clone() const { return TrackingData(*this); }

/**
 * @brief Assignment Operator
 *
 * @param other
 * @return TrackingData&
 */
TrackingData &TrackingData::operator=(const TrackingData &other) {
    roi = other.roi;
    return *this;
}
