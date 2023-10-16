#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_Error.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

enum HorizontalDirection { HORIZONTAL_TOP, HORIZONTAL_BOTTOM };

class BaseHorizontalCalibrationThread : public BaseThread,
                                        public PreviewableThread {
  public:
    BaseHorizontalCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~BaseHorizontalCalibrationThread();

    virtual CalibrationData getCalibrationData() = 0;

    void setPointAndExtend(cv::Point point);

    void setDirection(HorizontalDirection direction);
    HorizontalDirection getDirection();

    void setTopLine(Line line);
    Line getTopLine();
    virtual Line getRealTopLine() = 0;

    void setBottomLine(Line line);
    Line getBottomLine();
    virtual Line getRealBottomLine() = 0;

  protected:
    std::mutex m_mutex;
    Line topLine;
    Line bottomLine;

    HorizontalDirection direction = HORIZONTAL_TOP;

  protected:
    void updateTopLine(Line line);
    void updateBottomLine(Line line);

    bool isLineValid(Line &line);
};

class HorizontalCalibrationCameraThread
    : public BaseHorizontalCalibrationThread,
      public CameraAccessor,
      public ImageSizeCameraThread {
  public:
    HorizontalCalibrationCameraThread(wxEvtHandler *parent, CameraPtr &camera);
    ~HorizontalCalibrationCameraThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealTopLine() override;
    Line getRealBottomLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_HORIZONTAL_CALIBRATION_CAMERA;
};