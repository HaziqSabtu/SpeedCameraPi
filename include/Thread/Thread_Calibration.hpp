#pragma once

#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CalibrationThread : public wxThread {
  public:
    CalibrationThread(wxEvtHandler *parent,
                      std::unique_ptr<CameraBase> &camera);
    ~CalibrationThread();

    std::unique_ptr<CameraBase> getCamera();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::unique_ptr<CameraBase> camera;
};