/**
 * @file Thread_Process.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for processing ImageData
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

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