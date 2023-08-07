#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Error.hpp>
#include <Event/Event_LoadImage.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/FileReader/fileWR.hpp>

#include <memory>
#include <opencv2/opencv.hpp>

#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

class ReplayThread : public wxThread {
  public:
    ReplayThread(wxEvtHandler *parent, DataPtr data);
    ~ReplayThread();

    ThreadID getID() const;

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *parent;
    DataPtr data;

    const ThreadID id = THREAD_REPLAY;
};
