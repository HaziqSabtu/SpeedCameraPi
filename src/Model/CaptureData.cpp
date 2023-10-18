#include <Model/CaptureData.hpp>
#include <Utils/CommonUtils.hpp>

CaptureData::CaptureData() {}

CaptureData::CaptureData(cv::Mat image)
    : image(image), time(high_resolution_clock::now()) {}

CaptureData::CaptureData(cv::Mat image, HPTime time)
    : image(image), time(time) {}

bool CaptureData::operator==(const CaptureData &other) const {
    return Utils::isCvMatSameRandom(image, other.image, 50) &&
           time == other.time;
}

CaptureData CaptureData::clone() const { return CaptureData(*this); }

CaptureData &CaptureData::operator=(const CaptureData &other) {
    if (this == &other) // Handle self-assignment
        return *this;

    image = other.image.clone();
    time = other.time;
    return *this;
}
