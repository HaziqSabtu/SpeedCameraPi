#include <Model/TrackingData.hpp>

TrackingData::TrackingData() {}

TrackingData::TrackingData(cv::Rect roi) : roi(roi) {}

void TrackingData::clear() { roi = cv::Rect(); }

bool TrackingData::isInit() { return roi.area() > 0; }

bool TrackingData::operator==(const TrackingData &other) const {
    return roi == other.roi;
}

bool TrackingData::operator!=(const TrackingData &other) const {
    return !(*this == other);
}

TrackingData TrackingData::clone() const { return TrackingData(*this); }

TrackingData &TrackingData::operator=(const TrackingData &other) {
    roi = other.roi;
    return *this;
}
