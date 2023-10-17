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

class BaseLaneCalibrationThread : public BaseThread, public PreviewableThread {
  public:
    BaseLaneCalibrationThread(wxEvtHandler *parent, DataPtr data);
    ~BaseLaneCalibrationThread();

    void setPoint(cv::Point point);
    void clearPoint();

    virtual CalibrationData getCalibrationData() = 0;

    virtual Line getRealRightLine() = 0;
    virtual Line getRealLeftLine() = 0;

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

    bool isBothLineValid();
};

class LaneCalibrationCameraThread : public BaseLaneCalibrationThread,
                                    public CameraAccessor,
                                    public ImageSizeCameraThread {
  public:
    LaneCalibrationCameraThread(wxEvtHandler *parent, CameraPtr &camera);
    ~LaneCalibrationCameraThread();

    ThreadID getID() const override;

    CalibrationData getCalibrationData() override;

    Line getRealRightLine() override;
    Line getRealLeftLine() override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_LANE_CALIBRATION_CAMERA;
};