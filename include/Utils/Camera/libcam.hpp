#ifndef LIBCAM_HPP
#define LIBCAM_HPP

#include "CameraBase.hpp"
#include "LCCV/lccv.hpp"

class LibCam : public CameraBase {
    public:
      LibCam();
      ~LibCam();
      bool start();
      void stop();
      void setResolution(const int width, const int height);
      void setHeight(const int height);
      void setWidth(const int width);
      void setFPS(const int fps);
      void getFrame(cv::Mat &frame);

    private:
      lccv::PiCamera cam;
};

#endif