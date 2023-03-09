#ifndef LOAD_FILE_THREAD_HPP
#define LOAD_FILE_THREAD_HPP

#include <Event/Event_ProcessImage.hpp>
#include <Event/Event_UpdateImage.hpp>
#include <Thread/Task/Task_Load.hpp>
#include <Thread/ThreadPool.hpp>
#include <opencv2/opencv.hpp>
#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

class LoadFileThread : public wxThread {
  public:
    LoadFileThread(wxEvtHandler *parent, ThreadPool *threadPool,
                   std::vector<ImageData> *imgData, wxString path);
    ~LoadFileThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    ThreadPool *pool;
    std::vector<ImageData> *imgData;
    wxString path;
};

#endif