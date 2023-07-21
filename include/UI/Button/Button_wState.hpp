#pragma once

#include "UI/Button/Button_Default.hpp"
#include <wx/event.h>
#include <wx/wx.h>

class ButtonWState : public DefaultButton {

  public:
    ButtonWState(wxWindow *parent, wxWindowID id, const wxString &label,
                 bool initState = false, const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator &validator = wxDefaultValidator,
                 const wxString &name = wxButtonNameStr);
    ButtonWState(wxWindow *parent, wxWindowID id, const wxString &label,
                 const wxString &activeText, const wxString &inactiveText,
                 bool initState = false, const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize, long style = 0,
                 const wxValidator &validator = wxDefaultValidator,
                 const wxString &name = wxButtonNameStr);
    virtual ~ButtonWState();
    bool GetState();

  protected:
    virtual void render();
    virtual void toggleState();
    virtual void OnButton(wxCommandEvent &e) = 0;

    bool state;
    wxString activeText;
    wxString inactiveText;
};
