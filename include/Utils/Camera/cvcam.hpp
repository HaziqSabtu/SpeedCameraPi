#ifndef CVCAM_HPP
#define CVCAM_HPP

#include <opencv2/opencv.hpp>

#include "CameraBase.hpp"

/**
 * @brief Access camera with OpenCV
 *
 */
class CVCam : public CameraBase {
  public:
    CVCam();
    ~CVCam();
    bool start();
    void stop();
    void setResolution(const int width, const int height);
    void setHeight(const int height);
    void setWidth(const int width);
    void setFPS(const int fps);
    void getFrame(cv::Mat &frame);

  private:
    cv::VideoCapture cap;
};
#endif