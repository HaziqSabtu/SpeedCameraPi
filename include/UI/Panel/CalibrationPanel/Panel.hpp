#pragma once

#include "Event/Event_UpdatePreview.hpp"
#include "Model/CalibrationModel.hpp"
#include "Model/SessionData.hpp"
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

enum CalibrationText {
    IDLE,
    START_CALIBRATION,
    CALIBRATION_SUCCESS,
    CAMERA_ON,
    CAMERA_OFF
};

class CalibrationPanel : public wxPanel {
  public:
    CalibrationPanel(wxWindow *parent, wxWindowID id,
                     std::unique_ptr<CalibrationModel> &model);
    ~CalibrationPanel();

  private:
    const PanelID panel_id = PANEL_CALIBRATION;

    std::unordered_map<CalibrationText, wxString> calibText {
        {IDLE, wxT("Idle")},
        {START_CALIBRATION, wxT("Start Calibration")},
        {CALIBRATION_SUCCESS, wxT("Calibration Success")},
        {CAMERA_ON, wxT("Camera On")},
        {CAMERA_OFF, wxT("Camera Off")}};

    std::unique_ptr<CalibrationModel> model;

    CalibrationPanelButton *button_panel;
    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    wxBoxSizer *main_sizer;

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnCapture(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};