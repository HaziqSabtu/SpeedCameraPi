#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_CalibrationCamera.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CalibrationCaptureThread : public BaseCalibrationThread,
                                 public ImageSizeDataThread {
  public:
    CalibrationCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~CalibrationCaptureThread();

    ThreadID getID() const override;

    CalibrationData getCalibrationData() override;

    Line getRealLeftLine() override;
    Line getRealRightLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_CALIBRATION_CAPTURE;
};