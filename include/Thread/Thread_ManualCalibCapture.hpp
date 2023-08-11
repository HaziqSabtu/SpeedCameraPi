#pragma once

#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include "Utils/Struct/D_Line.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class ManualCalibrationCaptureThread : public BaseManualCalibrationThread {
  public:
    ManualCalibrationCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~ManualCalibrationCaptureThread();

    CalibData getCalibData();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    DataPtr data;

    const ThreadID threadID = ThreadID::THREAD_MANUAL_CALIBRATION_CAPTURE;
};