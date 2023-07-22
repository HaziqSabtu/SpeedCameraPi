#pragma once

#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationModel.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Base/Panel_Image.hpp>
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
    ManualCalibrationPanel(wxWindow *parent, wxWindowID id,
                           std::unique_ptr<CalibrationModel> &model);
    ~ManualCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_MANUAL_CALIBRATION;

    std::unique_ptr<CalibrationModel> model;

    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    ManualCalibrationPanelButton *button_panel;

    wxBoxSizer *main_sizer;

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnCapture(wxCommandEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);

    DECLARE_EVENT_TABLE()
};