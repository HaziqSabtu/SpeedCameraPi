#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <wx/wx.h>

class BaseThread : public wxThread {
  public:
    BaseThread(wxEvtHandler *parent, DataPtr data)
        : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {}
    virtual ~BaseThread() {};

    virtual ThreadID getID() const = 0;

  protected:
    DataPtr data;
    wxEvtHandler *parent;
};

class PreviewableThread {
  public:
    PreviewableThread() {
        AppConfig c;
        auto previewConfig = c.GetPreviewConfig();
        int pWidth = previewConfig.width;
        int pHeight = previewConfig.height;
        this->pSize = cv::Size(pWidth, pHeight);
    }

  protected:
    cv::Size pSize;
};

class ImageSizeDataThread {
  public:
    ImageSizeDataThread(DataPtr data) {
        auto captureData = data->getCaptureData();

        if (captureData.empty()) {
            throw std::runtime_error("Capture data is empty");
        }

        auto firstData = captureData.front();
        int iWidth = firstData.image.cols;
        int iHeight = firstData.image.rows;

        this->imageSize = cv::Size(iWidth, iHeight);
    }

  protected:
    cv::Size imageSize;
};

class ImageSizeCameraThread {
  public:
    ImageSizeCameraThread() {
        AppConfig c;
        auto cameraConfig = c.GetCameraConfig();
        int iWidth = cameraConfig.Camera_Width;
        int iHeight = cameraConfig.Camera_Height;
        this->imageSize = cv::Size(iWidth, iHeight);
    }

  protected:
    cv::Size imageSize;
};