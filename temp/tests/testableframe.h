#include "wx/event.h"
#include "wx/frame.h"

#include <unordered_map>
#include <wx/wx.h>

class wxTestableFrame : public wxFrame {
  public:
    wxTestableFrame();

    void OnEvent(wxEvent &evt);

  private:
    friend class EventCounter;

    int GetEventCount(wxEventType type);
    void ClearEventCount(wxEventType type);

    std::unordered_map<wxEventType, int> m_count;
};

class EventCounter {
  public:
    EventCounter(wxWindow *win, wxEventType type);
    ~EventCounter();

    int GetCount() { return m_frame->GetEventCount(m_type); }
    void Clear() { m_frame->ClearEventCount(m_type); }

    // Sometimes we need to yield a few times before getting the event we
    // expect, so provide a function waiting for the expected event for up to
    // the given number of milliseconds (supposed to be divisible by 50).
    //
    // Return true if we did receive the event or false otherwise.
    void WaitEvent(int timeInMs = 1000, int targetCount = 1);

    void WaitEventNoSkip(int timeInMs = 1000, int targetCount = 1);
    bool OldWaitEvent(int timeInMs = 1000);

  private:
    wxEventType m_type;
    wxTestableFrame *m_frame;
    wxWindow *m_win;
};

class TestApp : public wxApp {
  public:
    // LastEventCapture lastEventCapture;

    virtual bool OnInit();

    virtual int FilterEvent(wxEvent &event);

    int OnExit();

    void OnIdle(wxIdleEvent &event);
};