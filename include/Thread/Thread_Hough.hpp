#ifndef HOUGH_THREAD_HPP
#define HOUGH_THREAD_HPP

#include <Event/Event_Hough.hpp>
#include <Thread/Task/Task_HoughLine.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Struct/D_Hough.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

class HoughThread : public wxThread {
  public:
    HoughThread(wxEvtHandler *parent, ThreadPool *pool, ImageData &imgData);
    ~HoughThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    ThreadPool *pool;
    ImageData &imgData;
};

#endif