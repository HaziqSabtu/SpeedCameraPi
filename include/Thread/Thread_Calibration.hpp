#pragma once

#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

class CalibrationThread : public wxThread {
  public:
    CalibrationThread(wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
                      HSVFilter &hsvFilter, BFS &bfs, RansacLine &ransac);
    ~CalibrationThread();

    std::unique_ptr<CameraBase> getCamera();

    void setPoint(cv::Point point);

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::unique_ptr<CameraBase> camera;

    const ThreadID threadID = ThreadID::THREAD_CALIBRATION;

    HSVFilter hsvFilter;
    BFS bfs;
    RansacLine ransac;
};