#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class CaptureThread : public wxThread {
  public:
    CaptureThread(bool *isCapturing, bool *isProcessing, bool *isThreadRunning,
                  std::vector<ImageData> *imgData, cv::Mat *frame);
    virtual ~CaptureThread();

  private:
    virtual void *Entry();

    int maxFrameCount;
    int threadPoolCount;
    int frameInterval;
    int imageCount = 0;
    cv::Mat *frame;
    std::vector<ImageData> *imgData;

    bool *isCapturing;
    bool *isProcessing;
    bool *isThreadRunning;
};

#endif