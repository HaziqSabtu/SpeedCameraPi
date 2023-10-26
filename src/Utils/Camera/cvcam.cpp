#include <Utils/Camera/cvcam.hpp>

/**
 * @brief Construct a new CVCam::CVCam object
 *
 */
CVCam::CVCam() { cap = cv::VideoCapture(0); }

/**
 * @brief Destroy the CVCam::CVCam object
 *
 */
CVCam::~CVCam() { stop(); }

/**
 * @brief Start the camera
 *
 * @return true
 * @return false
 */
bool CVCam::start() {
    try {
        cap.open(0);
    } catch (...) {
        std::cout << "Error starting camera" << std::endl;
        return false;
    }
    return cap.isOpened();
}

/**
 * @brief Stop the camera
 *
 */
void CVCam::stop() {
    try {
        cap.release();
    } catch (...) {
        std::cout << "Error stopping camera" << std::endl;
    }
}

/**
 * @brief Set camera resolution
 *
 * @param width Width of the camera
 * @param height Height of the camera
 */
void CVCam::setResolution(const int width, const int height) {
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

/**
 * @brief Set camera FPS
 *
 * @param fps FPS of the camera
 */
void CVCam::setFPS(const int fps) { cap.set(cv::CAP_PROP_FPS, fps); }

/**
 * @brief Get frame from camera
 *
 * @param frame Frame from camera
 */
void CVCam::getFrame(cv::Mat &frame) {
    try {
        cap.read(frame);
    } catch (...) {
        std::cout << "Error getting frame" << std::endl;
    }
}

/**
 * @brief Set camera height
 *
 * @param height Height of the camera
 */
void CVCam::setHeight(const int height) {
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

/**
 * @brief Set camera width
 *
 * @param width Width of the camera
 */
void CVCam::setWidth(const int width) {
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
}