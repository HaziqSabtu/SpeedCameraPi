#pragma once

#include <wx/wx.h>

class ButtonInfo : public wxButton {
  public:
    ButtonInfo(wxWindow *parent);
    ~ButtonInfo();

  private:
    const wxSize size = wxSize(40, 40);
    const wxColour colour = wxColour(0, 121, 255);
    const wxString filename = wxT("info_24.ico");

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};