#ifndef HOUGH_THREAD_HPP
#define HOUGH_THREAD_HPP

#include <Event/Event_Hough.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

class HoughThread : public wxThread {
  public:
    HoughThread(wxEvtHandler *parent);
    ~HoughThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
};

#endif