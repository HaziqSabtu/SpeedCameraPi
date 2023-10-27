#include <Model/CaptureData.hpp>
#include <Utils/CommonUtils.hpp>

/**
 * @brief Construct a new CaptureData:: CaptureData object
 *
 */
CaptureData::CaptureData() {}

/**
 * @brief Construct a new CaptureData:: CaptureData object
 *
 * @param image The captured Image
 */
CaptureData::CaptureData(cv::Mat image)
    : image(image), time(high_resolution_clock::now()) {}

/**
 * @brief Construct a new CaptureData:: CaptureData object
 *
 * @param image
 * @param time
 */
CaptureData::CaptureData(cv::Mat image, HPTime time)
    : image(image), time(time) {}

/**
 * @brief Equal Operator
 *
 * @param other
 * @return true
 * @return false
 */
bool CaptureData::operator==(const CaptureData &other) const {
    return Utils::isCvMatSameRandom(image, other.image, 50) &&
           time == other.time;
}

/**
 * @brief Clone this CaptureData
 *
 * @return CaptureData
 */
CaptureData CaptureData::clone() const { return CaptureData(*this); }

/**
 * @brief Copy Assignment Operator
 *
 * @param other
 * @return CaptureData&
 */
CaptureData &CaptureData::operator=(const CaptureData &other) {
    if (this == &other) // Handle self-assignment
        return *this;

    image = other.image.clone();
    time = other.time;
    return *this;
}
