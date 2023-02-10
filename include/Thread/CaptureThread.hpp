#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <Utils/DataStruct.hpp>
#include <chrono>
#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class CaptureThread : public wxThread {
  public:
    CaptureThread(bool *isCapturing, std::vector<ImageData> *imgData,
                  cv::Mat *frame);
    virtual ~CaptureThread();

  private:
    virtual void *Entry();
    cv::Mat *frame;
    bool *isCapturing;
    std::vector<ImageData> *imgData;
    // CameraPanel m_parent;
};

#endif