#ifndef PROCESS_THREAD_HPP
#define PROCESS_THREAD_HPP

#include <Event/Event_ProcessImage.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Thread/Task/Task_OpticalFlow.hpp>
#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <opencv2/opencv.hpp>
#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

class ProcessThread : public wxThread {
  public:
    ProcessThread(wxEvtHandler *parent, ThreadPool *threadPool,
                  std::vector<ImageData> *imgData, OpticalFlowConfig ofConfig);
    ~ProcessThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    ThreadPool *pool;
    std::vector<ImageData> *imgData;
    OpticalFlowConfig ofConfig;
};

#endif