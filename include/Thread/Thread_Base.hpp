#pragma once

#include <Model/SessionData.hpp>

#include <Thread/Thread_ID.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>
#include <Utils/Config/AppConfig.hpp>

#include <opencv2/opencv.hpp>

#include <wx/wx.h>

#include <memory>
#include <string>

/**
 * @brief Base class for all Threads for ThreadController
 *
 */
class BaseThread : public wxThread {
  public:
    /**
     * @brief Construct a new BaseThread object
     *
     * @param parent View
     * @param data Pointer to the SessionData
     */
    BaseThread(wxEvtHandler *parent, DataPtr data)
        : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {}

    /**
     * @brief Destroy the Base Thread object
     *
     */
    virtual ~BaseThread() {};

    /**
     * @brief Get the ThreadID
     *
     * @return ThreadID
     */
    virtual ThreadID getID() const = 0;

  protected:
    DataPtr data;
    wxEvtHandler *parent;
};

/**
 * @brief Helper Class for BaseThread
 * @details Add a variable pSize, which is the size of the preview image. Also
 * enables the Thread to update the Image Panel.
 *
 */
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

/**
 * @brief Helper Class for BaseThread
 * @details Add a variable imageSize, which is the size of the captured data.
 *
 */
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

/**
 * @brief Helper Class for BaseThread
 * @details Add a variable imageSize, which is the size of the camera.
 *
 */
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