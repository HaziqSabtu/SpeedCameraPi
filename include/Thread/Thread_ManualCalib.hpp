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

class ManualCalibrationThread : public wxThread {
  public:
    ManualCalibrationThread(wxEvtHandler *parent,
                            std::unique_ptr<CameraBase> &camera);
    ~ManualCalibrationThread();

    std::unique_ptr<CameraBase> getCamera();

    CalibData getCalibData();

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);

    void setDirection(ManualDirection direction);
    ManualDirection getDirection();

    void setYellowLine(Detection::Line line);
    Detection::Line getYellowLine();

    void setBlueLine(Detection::Line line);
    Detection::Line getBlueLine();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::unique_ptr<CameraBase> camera;

    const ThreadID threadID = ThreadID::THREAD_MANUAL_CALIBRATION;

    std::mutex m_mutex;
    Detection::Line yellowLine;
    Detection::Line blueLine;

    ManualDirection direction = MANUAL_LEFT;

  private:
    void updateYellowLine(Detection::Line line);
    void updateBlueLine(Detection::Line line);

    bool isLineValid(Detection::Line &line);
};