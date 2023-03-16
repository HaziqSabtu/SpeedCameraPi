#ifndef LOAD_CAPTURE_THREAD_HPP
#define LOAD_CAPTURE_THREAD_HPP

#include <Event/Event_CaptureImage.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Utils/Config/AppConfig.hpp>

#include <memory>
#include <opencv2/opencv.hpp>
#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

class LoadCaptureThread : public wxThread {
  public:
    LoadCaptureThread(wxEvtHandler *parent, cv::VideoCapture *camera);
    ~LoadCaptureThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *parent;
    cv::VideoCapture *camera;
};

#endif