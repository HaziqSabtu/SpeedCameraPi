#include <Utils/Camera/libcam.hpp>

/**
 * @brief Construct a new Lib Cam:: Lib Cam object
 *
 */
LibCam::LibCam() {}

/**
 * @brief Destroy the Lib Cam:: Lib Cam object
 *
 */
LibCam::~LibCam() { stop(); }

/**
 * @brief Start the camera
 *
 * @return true
 * @return false
 */
bool LibCam::start() { return cam.startVideo(); }

/**
 * @brief Stop the camera
 *
 */
void LibCam::stop() {
    try {
        cam.stopVideo();
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
void LibCam::setResolution(const int width, const int height) {
    cam.options->video_width = width;
    cam.options->video_height = height;
}

/**
 * @brief Set camera FPS
 *
 * @param fps FPS of the camera
 */
void LibCam::setFPS(const int fps) {
    cam.options->framerate = fps;
    cam.options->verbose = true;
}

/**
 * @brief Get frame from camera
 *
 * @param frame Frame from camera
 */
void LibCam::getFrame(cv::Mat &frame) {
    try {
        cam.getVideoFrame(frame, 1000);
    } catch (...) {
        std::cout << "Error getting frame" << std::endl;
    }
}

/**
 * @brief Set camera height
 *
 * @param height Height of the camera
 */
void LibCam::setHeight(const int height) {
    cam.options->video_height = height;
    std::cout << "Height: " << cam.options->video_height << std::endl;
}

/**
 * @brief Set camera width
 *
 * @param width Width of the camera
 */
void LibCam::setWidth(const int width) {
    cam.options->video_width = width;
    std::cout << "Width: " << cam.options->video_width << std::endl;
}