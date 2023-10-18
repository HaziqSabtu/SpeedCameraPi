#include <Model/AllignData.hpp>
#include <Utils/CommonUtils.hpp>

AllignData::AllignData() {}

AllignData::AllignData(cv::Mat image, cv::Mat transformMatrix)
    : transformMatrix(transformMatrix), image(image) {}

bool AllignData::operator==(const AllignData &other) const {
    return Utils::isCvMatSame(image, other.image) &&
           Utils::isCvMatSame(transformMatrix, other.transformMatrix);
}

AllignData AllignData::clone() const { return AllignData(*this); }

AllignData &AllignData::operator=(const AllignData &other) {
    if (this == &other) // Handle self-assignment
        return *this;

    image = other.image.clone();
    transformMatrix = other.transformMatrix.clone();
    return *this;
}
