#ifndef TEMP_HPP
#define TEMP_HPP

#include <Event/UpdateImageEvent.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

class ImageThread : public wxThread {
  public:
    ImageThread(wxEvtHandler *parent, cv::VideoCapture *cap);
    ~ImageThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    cv::VideoCapture *m_cap;
};

#endif