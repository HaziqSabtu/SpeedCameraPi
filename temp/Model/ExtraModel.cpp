#include <>

ColorCalibExtraModel::ColorCalibExtraModel() {
    lower_blue = DEF_lower_blue;
    upper_blue = DEF_upper_blue;
    lower_yellow = DEF_lower_yellow;
    upper_yellow = DEF_upper_yellow;
}

ColorCalibExtraModel::~ColorCalibExtraModel() {}

ColorCalibExtraModel::ColorCalibExtraModel(const ColorCalibExtraModel &other) {
    lower_blue = other.lower_blue;
    upper_blue = other.upper_blue;
    lower_yellow = other.lower_yellow;
    upper_yellow = other.upper_yellow;
}

ColorCalibExtraModel ColorCalibExtraModel::clone() const {
    return ColorCalibExtraModel(*this);
}

ColorCalibExtraModel &
ColorCalibExtraModel::operator=(const ColorCalibExtraModel &other) {
    if (this == &other) // Handle self-assignment
        return *this;

    lower_blue = other.lower_blue;
    upper_blue = other.upper_blue;
    lower_yellow = other.lower_yellow;
    upper_yellow = other.upper_yellow;

    return *this;
}

bool ColorCalibExtraModel::isBlueCalibrated() {
    return lower_blue != cv::Scalar(0, 0, 0) &&
           upper_blue != cv::Scalar(0, 0, 0);
}

bool ColorCalibExtraModel::isYellowCalibrated() {
    return lower_yellow != cv::Scalar(0, 0, 0) &&
           upper_yellow != cv::Scalar(0, 0, 0);
}

void ColorCalibExtraModel::setBlueRange(
    std::pair<cv::Scalar, cv::Scalar> range) {
    lower_blue = range.first;
    upper_blue = range.second;
}

void ColorCalibExtraModel::setYellowRange(
    std::pair<cv::Scalar, cv::Scalar> range) {
    lower_yellow = range.first;
    upper_yellow = range.second;
}

std::pair<cv::Scalar, cv::Scalar> ColorCalibExtraModel::getBlueRange() {
    return std::make_pair(lower_blue, upper_blue);
}

std::pair<cv::Scalar, cv::Scalar> ColorCalibExtraModel::getYellowRange() {
    return std::make_pair(lower_yellow, upper_yellow);
}

void ColorCalibExtraModel::resetBlueRange() {
    lower_blue = DEF_lower_blue;
    upper_blue = DEF_upper_blue;
}

void ColorCalibExtraModel::resetYellowRange() {
    lower_yellow = DEF_lower_yellow;
    upper_yellow = DEF_upper_yellow;
}
