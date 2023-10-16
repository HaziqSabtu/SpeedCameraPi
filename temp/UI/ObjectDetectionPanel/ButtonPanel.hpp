#ifndef OBJECT_DETECTION_PANEL_BUTTON
#define OBJECT_DETECTION_PANEL_BUTTON

#include <Algorithm/object_tracker/OpticalFlowTracker.hpp>
#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class ObjectDetectionPanelButton : public wxPanel {
  public:
    ObjectDetectionPanelButton(wxWindow *parent, wxWindowID id);
    void enableAllButtons();
    void disableAllButtons();

    void OnBBox();
    void OnOptF();
    void OnBotL();
    void OnLine();

  private:
    bool isBBox = false;
    bool isOptF = false;
    bool isBotL = false;
    bool isLine = false;

    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxButton *Replay_Button;
    wxButton *BBox_Button;
    wxButton *OptF_Button;
    wxButton *BotL_Button;
    wxButton *Line_Button;
    wxButton *Speed_Button;
    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE()
};
#endif
