#pragma once

#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_ID.hpp"
#include "Utils/Struct/D_Line.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

enum ManualDirection { MANUAL_LEFT, MANUAL_RIGHT };

class BaseManualCalibrationThread : public wxThread {
  public:
    BaseManualCalibrationThread(wxEvtHandler *parent);
    ~BaseManualCalibrationThread();

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);
    void setPoint2f(cv::Point point);

    void setDirection(ManualDirection direction);
    ManualDirection getDirection();

    void setYellowLine(Line line);
    Line getYellowLine();

    void setBlueLine(Line line);
    Line getBlueLine();

    virtual ThreadID getID() const = 0;

  protected:
    wxEvtHandler *parent;

    std::mutex m_mutex;
    Line yellowLine;
    Line blueLine;

    ManualDirection direction = MANUAL_LEFT;

    cv::Size pSize;

  protected:
    void updateYellowLine(Line line);
    void updateBlueLine(Line line);

    bool isLineValid(Line &line);
};

class ManualCalibrationThread : public BaseManualCalibrationThread {
  public:
    ManualCalibrationThread(wxEvtHandler *parent,
                            std::unique_ptr<CameraBase> &camera);
    ~ManualCalibrationThread();

    std::unique_ptr<CameraBase> getCamera();

    CalibData getCalibData();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    std::unique_ptr<CameraBase> camera;

    const ThreadID threadID = ThreadID::THREAD_MANUAL_CALIBRATION;
};