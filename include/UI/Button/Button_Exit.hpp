#pragma once

#include <wx/wx.h>

class ButtonExit : public wxButton {
  public:
    ButtonExit(wxWindow *parent);
    ~ButtonExit();

  private:
    wxSize size = wxSize(40, 40);
    wxString text = wxT("Exit");
    wxColour colour = wxColour(234, 84, 85);

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};