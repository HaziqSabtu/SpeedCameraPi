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

class RoiThread : public wxThread {
  public:
    RoiThread(wxEvtHandler *parent, ImageDataPtr imageData);
    ~RoiThread();

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);

    bool isRectValid();

    cv::Rect getRect();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    ImageDataPtr imageData;

    const ThreadID threadID = ThreadID::THREAD_ROI;

    std::mutex m_mutex;

    cv::Point p1 = cv::Point(-1, -1);
    cv::Point p2 = cv::Point(-1, -1);

  private:
};