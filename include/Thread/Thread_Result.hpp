#ifndef RESULT_THREAD_HPP
#define RESULT_THREAD_HPP

#include <Event/Event_UpdateImage.hpp>
#include <Utils/DataStruct.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class ResultThread : public wxThread {
  public:
    ResultThread(wxEvtHandler *parent, std::vector<ImageData> *imgData);
    ~ResultThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::vector<ImageData> *imgData;
};

#endif