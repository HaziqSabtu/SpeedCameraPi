#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CaptureCalibrationThread : public BaseCalibrationThread {
  public:
    CaptureCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~CaptureCalibrationThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    DataPtr data;

    const ThreadID threadID = ThreadID::THREAD_CALIBRATION_CAPTURE;
};