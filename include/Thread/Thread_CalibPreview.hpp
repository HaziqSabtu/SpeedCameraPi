#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Capture.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CalibPreviewThread : public wxThread {
  public:
    CalibPreviewThread(wxEvtHandler *parent,
                       std::unique_ptr<CameraBase> &camera, DataPtr data);
    ~CalibPreviewThread();

    std::unique_ptr<CameraBase> getCamera();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::unique_ptr<CameraBase> camera;
    DataPtr data;

    const ThreadID id = THREAD_CALIBRATION_PREVIEW;
};
