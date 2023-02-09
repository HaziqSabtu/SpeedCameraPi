#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class CaptureThread : public wxThread {
  public:
    // CaptureThread(Panel2 *p);
    // CaptureThread();
    CaptureThread(bool *isCapturing,
                  std::vector<std::pair<cv::Mat, time_t>> *imgData,
                  cv::Mat *frame);
    virtual ~CaptureThread();

  private:
    virtual void *Entry();
    cv::Mat *frame;
    bool *isCapturing;
    std::vector<std::pair<cv::Mat, time_t>> *imgData;
    // CameraPanel m_parent;
};

#endif