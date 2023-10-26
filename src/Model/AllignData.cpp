#include <Model/AllignData.hpp>
#include <Utils/CommonUtils.hpp>

/**
 * @brief Construct a new AllignData:: AllignData object
 *
 */
AllignData::AllignData() {}

/**
 * @brief Construct a new AllignData:: AllignData object
 *
 * @param image The alligned Image
 * @param transformMatrix The transformation Matrix
 */
AllignData::AllignData(cv::Mat image, cv::Mat transformMatrix)
    : transformMatrix(transformMatrix), image(image) {}

/**
 * @brief Compare two AllignData
 *
 * @param other the other AllignData
 * @return true if equal
 * @return false if not equal
 */
bool AllignData::operator==(const AllignData &other) const {
    return Utils::isCvMatSame(image, other.image) &&
           Utils::isCvMatSame(transformMatrix, other.transformMatrix);
}

/**
 * @brief Clone this AllignData
 *
 * @return AllignData
 */
AllignData AllignData::clone() const { return AllignData(*this); }

/**
 * @brief Copy Assignment Operator
 *
 * @param other the other AllignData
 * @return AllignData&
 */
AllignData &AllignData::operator=(const AllignData &other) {
    if (this == &other) // Handle self-assignment
        return *this;

    image = other.image.clone();
    transformMatrix = other.transformMatrix.clone();
    return *this;
}
