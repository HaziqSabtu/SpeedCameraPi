#ifndef SELECT_LINE_PANEL_BUTTON
#define SELECT_LINE_PANEL_BUTTON

#include <UI/SelectLinePanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class SelectLinePanelButton : public wxPanel {
  public:
    SelectLinePanelButton(wxWindow *parent, wxWindowID id);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};
#endif
