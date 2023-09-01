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

class RoiThread : public BaseThread, PreviewableThread {
  public:
    RoiThread(wxEvtHandler *parent, DataPtr data);
    ~RoiThread();

    ThreadID getID() const override;

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);

    bool isRectValid();

    cv::Rect getRect();

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_ROI;

    std::mutex m_mutex;

    cv::Point p1 = cv::Point(-1, -1);
    cv::Point p2 = cv::Point(-1, -1);
};