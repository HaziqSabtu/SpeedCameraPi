#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class CaptureThread : public wxThread {
  public:
    // CaptureThread(Panel2 *p);
    CaptureThread();
    virtual ~CaptureThread();

  private:
    virtual void *Entry();
    // Panel2 *m_parent;
};

#endif