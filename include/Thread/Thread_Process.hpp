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

#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_ProcessImage.hpp>
#include <Event/Event_UpdatePreview.hpp>
#include <Thread/Task/Task_OpticalFlow.hpp>
#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

/**
 * @brief Custom wxThread for processing ImageData
 *
 */
class ProcessThread : public wxThread {
  public:
    ProcessThread(wxEvtHandler *parent, POOLPtr threadPool, DataPtr data);
    ~ProcessThread();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    POOLPtr pool;
    DataPtr data;

    const ThreadID threadID = ThreadID::THREAD_PROCESS;
};

#endif