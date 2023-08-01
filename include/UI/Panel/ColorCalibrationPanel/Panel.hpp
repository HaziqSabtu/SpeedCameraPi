#pragma once

#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelBlueStatus.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelYellowStatus.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/ColorCalibrationPanel/Panel_Button.hpp>
#include <UI/Panel/Common/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ColorCalibrationPanel : public wxPanel {
  public:
    ColorCalibrationPanel(wxWindow *parent, wxWindowID id, CCCPtr &controller);
    ~ColorCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_COLOR_CALIBRATION;

    CCCPtr controller;

    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    ColorCalibrationPanelButton *button_panel;

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