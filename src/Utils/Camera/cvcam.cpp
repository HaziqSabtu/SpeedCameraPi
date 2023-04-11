#include <Utils/Camera/cvcam.hpp>

CVCam::CVCam() { cap = cv::VideoCapture(0); }

CVCam::~CVCam() { stop(); }

bool CVCam::start() {
      try {
            cap.open(0);
      } catch (...) {
            std::cout << "Error starting camera" << std::endl;
            return false;
      }
      return cap.isOpened();
}

void CVCam::stop() {
      try {
            cap.release();
      } catch (...) {
            std::cout << "Error stopping camera" << std::endl;
      }
}

void CVCam::setResolution(const int width, const int height) {
      cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
      cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

void CVCam::setFPS(const int fps) { cap.set(cv::CAP_PROP_FPS, fps); }

void CVCam::getFrame(cv::Mat &frame) {
      try {
            cap.read(frame);
      } catch (...) {
            std::cout << "Error getting frame" << std::endl;
      }
}

void CVCam::setHeight(const int height) {
      cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

void CVCam::setWidth(const int width) {
      cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
}