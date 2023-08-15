#pragma once

#include "Model/ExtraModel.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Capture.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class ColorCalibPreviewThread : public wxThread {
  public:
    ColorCalibPreviewThread(wxEvtHandler *parent,
                            std::unique_ptr<CameraBase> &camera,
                            CCModelPtr ccExtraModel);
    ~ColorCalibPreviewThread();

    std::unique_ptr<CameraBase> getCamera();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

    bool isCalibrationComplete();

  private:
    wxEvtHandler *parent;
    std::unique_ptr<CameraBase> camera;
    CCModelPtr ccExtraModel;

    const ThreadID id = THREAD_COLOR_CALIBRATION_PREVIEW;
};
