#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <Algorithm/image_stabilizer/FeatureDetector.hpp>

#include <Thread/ProcessThread.hpp>
#include <Thread/SIFTTask.hpp>
#include <Thread/ThreadPool.hpp>
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
    std::array<wxThread *, 100> g_ThreadArray;
    std::size_t g_ThreadArrayIndex = 0;

    FeatureDetector featureDetector;
};

#endif