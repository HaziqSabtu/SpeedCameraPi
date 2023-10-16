#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

enum ManualDirection { MANUAL_LEFT, MANUAL_RIGHT };

class BaseManualCalibrationThread : public BaseThread,
                                    public PreviewableThread {
  public:
    BaseManualCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~BaseManualCalibrationThread();

    virtual CalibrationData getCalibrationData() = 0;

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);
    void setPoint2AndExtend(cv::Point point);

    void setDirection(ManualDirection direction);
    ManualDirection getDirection();

    void setRightLine(Line line);
    Line getRightLine();
    virtual Line getRealRightLine() = 0;

    void setLeftLine(Line line);
    Line getLeftLine();
    virtual Line getRealLeftLine() = 0;

  protected:
    std::mutex m_mutex;
    Line rightLine;
    Line leftLine;

    ManualDirection direction = MANUAL_LEFT;

  protected:
    void updateRightLine(Line line);
    void updateLeftLine(Line line);

    bool isLineValid(Line &line);
};

class ManualCalibrationCameraThread : public BaseManualCalibrationThread,
                                      public CameraAccessor,
                                      public ImageSizeCameraThread {
  public:
    ManualCalibrationCameraThread(wxEvtHandler *parent, CameraPtr &camera);
    ~ManualCalibrationCameraThread();

    CalibrationData getCalibrationData() override;

    ThreadID getID() const override;

    Line getRealRightLine() override;
    Line getRealLeftLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_MANUAL_CALIBRATION_CAMERA;
};