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

class ColorCalibrationThread : public wxThread {
  public:
    ColorCalibrationThread(wxEvtHandler *parent,
                           std::unique_ptr<CameraBase> &camera,
                           HSVFilter &hsvFilter, BFS &bfs);
    ~ColorCalibrationThread();

    std::unique_ptr<CameraBase> getCamera();

    void setPoint(cv::Point point);

    CalibData getCalibData();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::unique_ptr<CameraBase> camera;

    const ThreadID threadID = ThreadID::THREAD_COLOR_CALIBRATION;

    HSVFilter hsvFilter;
    BFS bfs;

    std::mutex m_mutex;
    cv::Point point;
    Detection::Line yellowLine;
    Detection::Line blueLine;

  private:
    void updateYellowLine(Detection::Line line);
    void updateBlueLine(Detection::Line line);
};