#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class BaseCalibrationThread : public wxThread {
  public:
    BaseCalibrationThread(wxEvtHandler *parent);
    ~BaseCalibrationThread();

    void setPoint(cv::Point point);
    void clearPoint();

    CalibrationData getCalibData();

    virtual ThreadID getID() const = 0;

  protected:
    wxEvtHandler *parent;

    cv::Size pSize;

    HSVFilter hsvFilter;
    BFS bfs;
    RansacLine ransac;

    std::mutex m_mutex;
    cv::Point point;
    Line yellowLine;
    Line blueLine;

  protected:
    void updateYellowLine(Line line);
    void updateBlueLine(Line line);
};

class CalibrationThread : public BaseCalibrationThread {
  public:
    CalibrationThread(wxEvtHandler *parent,
                      std::unique_ptr<CameraBase> &camera);
    ~CalibrationThread();

    std::unique_ptr<CameraBase> getCamera();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    std::unique_ptr<CameraBase> camera;

    const ThreadID threadID = ThreadID::THREAD_CALIBRATION;
};