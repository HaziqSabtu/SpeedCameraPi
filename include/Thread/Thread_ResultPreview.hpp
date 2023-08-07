#pragma once

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

class ResultPreviewThread : public wxThread {
  public:
    ResultPreviewThread(wxEvtHandler *parent, DataPtr data);
    ~ResultPreviewThread();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    DataPtr data;

    const ThreadID threadID = ThreadID::THREAD_RESULT_PREVIEW;
};
