#ifndef DEMO_THREAD_HPP
#define DEMO_THREAD_HPP

#include <Thread/SIFTTask.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/DataStruct.hpp>
#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class DemoThread : public wxThread {
  public:
    DemoThread(bool *isCapturing, bool *isProcessing, bool *isThreadRunning,
               std::vector<ImageData> *imgData);
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