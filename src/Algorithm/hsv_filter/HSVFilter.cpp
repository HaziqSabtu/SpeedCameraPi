#include <Algorithm/hsv_filter/HSVFilter.hpp>

/**
 * @brief Construct a new HSVFilter::HSVFilter object
 * 
 */
HSVFilter::HSVFilter() {}

/**
 * @brief Convert an image from BGR color space to HSV color space.
 *
 * @param src The source image (assumed to be in BGR format).
 * @return The resulting image in HSV color space.
 * @note This method assumes that the input image is of type BGR; no check is performed. Maybe something can be implemented in the future.
 */
cv::Mat HSVFilter::toHSV(cv::Mat &src) {
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    return hsv;
}

/**
 * @brief Apply a filter to an HSV image based on specified color range.
 *
 * @param hsv The HSV image.
 * @param lower The lower bound of the color range.
 * @param upper The upper bound of the color range.
 * @return The filtered mask.
 */
cv::Mat HSVFilter::filter(cv::Mat &hsv, cv::Scalar lower, cv::Scalar upper) {
    cv::Mat mask;
    cv::inRange(hsv, lower, upper, mask);
    return mask;
}

/**
 * @brief Apply a red color mask to an HSV image.
 *
 * @param hsv The HSV image.
 * @return The red color mask.
 */
cv::Mat HSVFilter::redMask(cv::Mat &hsv) {
    cv::Mat mask1 = filter(hsv, lower_red1, upper_red1);
    cv::Mat mask2 = filter(hsv, lower_red2, upper_red2);
    cv::Mat mask = mask1 | mask2;
    return mask;
}

/**
 * @brief Apply a yellow color mask to an HSV image.
 *
 * @param hsv The HSV image.
 * @return The yellow color mask.
 */
cv::Mat HSVFilter::yellowMask(cv::Mat &hsv) {
    cv::Mat mask = filter(hsv, lower_yellow, upper_yellow);
    return mask;
}

/**
 * @brief Apply a blue color mask to an HSV image.
 *
 * @param hsv The HSV image.
 * @return The blue color mask.
 */
cv::Mat HSVFilter::blueMask(cv::Mat &hsv) {
    cv::Mat mask = filter(hsv, lower_blue, upper_blue);
    return mask;
}

/**
 * @brief Set the lower and upper bounds of the red1 color range.
 * 
 * @param lower_red The lower bound of the red1 color range.
 * @param upper_red The upper bound of the red1 color range.
 */
void HSVFilter::setRed1(cv::Scalar lower_red, cv::Scalar upper_red) {
    this->lower_red1 = lower_red;
    this->upper_red1 = upper_red;
}

/**
 * @brief Set the lower and upper bounds of the red2 color range.
 * 
 * @param lower_red The lower bound of the red2 color range.
 * @param upper_red The upper bound of the red2 color range.
 */
void HSVFilter::setRed2(cv::Scalar lower_red, cv::Scalar upper_red) {
    this->lower_red2 = lower_red;
    this->upper_red2 = upper_red;
}

/**
 * @brief Set the lower and upper bounds of the yellow color range.
 * 
 * @param lower_yellow The lower bound of the yellow color range.
 * @param upper_yellow The upper bound of the yellow color range.
 */
void HSVFilter::setYellow(cv::Scalar lower_yellow, cv::Scalar upper_yellow) {
    this->lower_yellow = lower_yellow;
    this->upper_yellow = upper_yellow;
}

/**
 * @brief Set the lower and upper bounds of the blue color range.
 * 
 * @param lower_blue The lower bound of the blue color range.
 * @param upper_blue The upper bound of the blue color range.
 */
void HSVFilter::setBlue(cv::Scalar lower_blue, cv::Scalar upper_blue) {
    this->lower_blue = lower_blue;
    this->upper_blue = upper_blue;
}
