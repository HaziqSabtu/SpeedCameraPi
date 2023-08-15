#ifndef DEMO_THREAD_HPP
#define DEMO_THREAD_HPP

#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class DemoThread : public wxThread {
  public:
    DemoThread(bool *isCapturing, bool *isProcessing, bool *isThreadRunning,
               std::vector<ImageData> *imgData, int maxLoadFrame);
    virtual ~DemoThread();

  private:
    virtual void *Entry();

    int imageCount = 0;
    std::vector<ImageData> *imgData;

    bool *isCapturing;
    bool *isProcessing;
    bool *isThreadRunning;
};

#endif