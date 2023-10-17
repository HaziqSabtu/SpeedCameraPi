#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LaneManualCalibrationCamera.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class LaneManualCalibrationCaptureThread
    : public BaseLaneManualCalibrationThread,
      public ImageSizeDataThread {
  public:
    LaneManualCalibrationCaptureThread(wxEvtHandler *parent, DataPtr data);
    ~LaneManualCalibrationCaptureThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealRightLine() override;
    Line getRealLeftLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAPTURE;
};