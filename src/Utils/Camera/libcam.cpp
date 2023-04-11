#include <Utils/Camera/libcam.hpp>

LibCam::LibCam() {}

LibCam::~LibCam() { stop(); }

bool LibCam::start() { return cam.startVideo(); }

void LibCam::stop() {
      try {
            cam.stopVideo();
      } catch (...) {
            std::cout << "Error stopping camera" << std::endl;
      }
}

void LibCam::setResolution(const int width, const int height) {
      cam.options->video_width = width;
      cam.options->video_height = height;
}

void LibCam::setFPS(const int fps) {
      cam.options->framerate = fps;
      cam.options->verbose = true;
}

void LibCam::getFrame(cv::Mat &frame) {
      try {
            cam.getVideoFrame(frame, 1000);
      } catch (...) {
            std::cout << "Error getting frame" << std::endl;
      }
}

void LibCam::setHeight(const int height) {
      cam.options->video_height = height;
      std::cout << "Height: " << cam.options->video_height << std::endl;
}

void LibCam::setWidth(const int width) {
      cam.options->video_width = width;
      std::cout << "Width: " << cam.options->video_width << std::endl;
}