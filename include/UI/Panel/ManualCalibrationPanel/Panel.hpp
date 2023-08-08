#pragma once

#include "Controller/ManualCalibrationController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Common/Panel_Image.hpp>
#include <UI/Panel/ManualCalibrationPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationPanel : public wxPanel {
  public:
    ManualCalibrationPanel(wxWindow *parent, wxWindowID id, MCCPtr &controller);
    ~ManualCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_MANUAL_CALIBRATION;

    MCCPtr controller;

    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    ManualCalibrationPanelButton *button_panel;

    wxBoxSizer *main_sizer;

    void unBindImagePanel();

    void TogglePreviewButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationButtonHandler(BitmapButtonT2 *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnCapture(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnMotion(wxMouseEvent &e);
    void OnLeftUp(wxMouseEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);
    void OnUpdateState(UpdateStateEvent &e);
    void OnShow(wxShowEvent &e);

    DECLARE_EVENT_TABLE()
};