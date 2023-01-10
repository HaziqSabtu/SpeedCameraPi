#ifndef OTHER_FRAME_HPP
#define OTHER_FRAME_HPP
#include <wx/wx.h>

enum { ID_BUTTON2 = 1 };

class OtherFrame : public wxFrame {
  public:
    OtherFrame();
    void OnOpenFrame1(wxCommandEvent &event);

  private:
    wxButton *m_button;
    wxDECLARE_EVENT_TABLE();
};

#endif