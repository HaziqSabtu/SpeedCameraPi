#pragma once

#include "Controller/CalibrationController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Base/Panel_Image.hpp>
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

// TODO: Cleanup
enum CalibrationText {
    IDLE,
    START_CALIBRATION,
    CALIBRATION_SUCCESS,
    CAMERA_ON,
    CAMERA_OFF
};

class CalibrationPanel : public wxPanel {
  public:
    CalibrationPanel(wxWindow *parent, wxWindowID id, CLCPtr &controller);
    ~CalibrationPanel();

  private:
    const PanelID panel_id = PANEL_CALIBRATION;

    CLCPtr controller;

    CalibrationPanelButton *button_panel;
    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    wxBoxSizer *main_sizer;

    void OnToggleCameraButton(BitmapButtonT2 *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnCapture(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);
    void OnUpdateState(UpdateStateEvent &e);
    void OnShow(wxShowEvent &e);

    DECLARE_EVENT_TABLE()
};