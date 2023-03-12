#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <Event/Event_UpdateImage.hpp>
#include <Utils/DataStruct.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

class CaptureThread : public wxThread {
  public:
    CaptureThread(wxEvtHandler *parent, cv::VideoCapture *cap);
    ~CaptureThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    cv::VideoCapture *m_cap;
};

#endif