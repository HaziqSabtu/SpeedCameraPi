#pragma once

#include "Event/Event_UpdatePreview.hpp"
#include "Model/CalibrationModel.hpp"
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
    std::unique_ptr<CalibrationModel> model;

    CalibrationPanelButton *button_panel;
    BaseImagePanel *img_bitmap;

    wxStaticText *staticText;

    wxBoxSizer *text_sizer;
    wxBoxSizer *main_sizer;

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};