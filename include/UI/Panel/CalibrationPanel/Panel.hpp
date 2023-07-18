#pragma once

#include "Event/Event_UpdatePreview.hpp"
#include "Model/CalibrationModel.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Base/Panel_Image.hpp>
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationPanel : public wxPanel {
  public:
    CalibrationPanel(wxWindow *parent, wxWindowID id,
                     std::unique_ptr<CalibrationModel> &model);
    ~CalibrationPanel();

  private:
    const PanelID panel_id = PANEL_CALIBRATION;

    std::unique_ptr<CalibrationModel> model;

    CalibrationPanelButton *button_panel;
    BaseImagePanel *img_bitmap;

    ButtonExit *exit_Button;

    TitleText *titleText;
    StatusText *statusText;

    wxBoxSizer *title_Sizer;
    wxBoxSizer *main_sizer;

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};