#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class BaseCalibrationThread : public BaseThread, public PreviewableThread {
  public:
    BaseCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~BaseCalibrationThread();

    void setPoint(cv::Point point);
    void clearPoint();

    CalibrationData getCalibrationData();

  protected:
    HSVFilter hsvFilter;
    BFS bfs;
    RansacLine ransac;

    std::mutex m_mutex;
    cv::Point point;
    Line rightLine; // yellow line
    Line leftLine;  // blue line

  protected:
    void updateRightLine(Line line);
    void updateLeftLine(Line line);
};

class CalibrationCameraThread : public BaseCalibrationThread,
                                public CameraAccessor {
  public:
    CalibrationCameraThread(wxEvtHandler *parent, CameraPtr &camera);
    ~CalibrationCameraThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_CALIBRATION_CAMERA;
};