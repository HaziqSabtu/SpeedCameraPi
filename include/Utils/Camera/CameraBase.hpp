#ifndef CAMERA_BASE_HPP
#define CAMERA_BASE_HPP

#include <opencv2/opencv.hpp>

#define CameraPtr std::unique_ptr<CameraBase>

class CameraBase {

  public:
    virtual bool start() = 0;
    virtual void stop() = 0;
    virtual void setResolution(const int width, const int height) = 0;
    virtual void setHeight(const int height) = 0;
    virtual void setWidth(const int width) = 0;
    virtual void setFPS(const int fps) = 0;
    virtual void getFrame(cv::Mat &frame) = 0;
};

class CameraAccessor {
  public:
    CameraAccessor(CameraPtr &camera) : camera(std::move(camera)) {}

    CameraPtr getCamera() { return std::move(camera); }
    void setCamera(CameraPtr camera) { this->camera = std::move(camera); }

  protected:
    CameraPtr camera;
};

#endif