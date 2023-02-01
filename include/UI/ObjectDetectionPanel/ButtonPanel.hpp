#ifndef OBJECT_DETECTION_PANEL_BUTTON
#define OBJECT_DETECTION_PANEL_BUTTON

#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class ObjectDetectionPanelButton : public wxPanel {
  public:
    ObjectDetectionPanelButton(wxWindow *parent, wxWindowID id);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;

    DECLARE_EVENT_TABLE()
};
#endif
