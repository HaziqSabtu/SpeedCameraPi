#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <Event/Event_UpdateImage.hpp>
#include <Utils/DataStruct.hpp>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include <string>
#include <wx/thread.h>

class CaptureThread : public wxThread {
  public:
    CaptureThread(wxEvtHandler *parent, raspicam::RaspiCam_Cv *cap);
    ~CaptureThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    raspicam::RaspiCam_Cv *m_cap;
};

#endif