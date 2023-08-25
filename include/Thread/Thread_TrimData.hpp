#pragma once

#include "Algorithm/Struct/D_Line.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Calibration.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

enum TrimDataThreadCurrentStatus {
    TRIM_NONE,
    TRIM_START,
    TRIM_END,
    TRIM_PREVIEW,
};

class TrimDataThread : public wxThread {
  public:
    TrimDataThread(wxEvtHandler *parent, DataPtr data);
    ~TrimDataThread();

    void processTrimData();

    void incrementStartPos();
    void decrementStartPos();

    bool isStartIncrementable();
    bool isStartDecrementable();

    void incrementEndPos();
    void decrementEndPos();

    bool isEndIncrementable();
    bool isEndDecrementable();

    void setStatus(TrimDataThreadCurrentStatus status);
    TrimDataThreadCurrentStatus getStatus();

    ThreadID getID() const;

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    DataPtr data;

    const ThreadID threadID = ThreadID::THREAD_TRIM_DATA;
    const int MILLI_SLEEP = 100;

    TrimDataThreadCurrentStatus status =
        TrimDataThreadCurrentStatus::TRIM_START;

    std::mutex m_mutex;

    int startPos = -1;
    int endPos = -1;

    const int MAX_FRAME;
    const int MIN_ALLOWED_FRAME = 5;

    cv::Size pSize;

    int getFrameRange();
};