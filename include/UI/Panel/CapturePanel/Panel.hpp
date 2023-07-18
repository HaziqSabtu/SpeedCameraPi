#pragma once

#include "Model/SessionData.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/Panel/RoiPanel/Panel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
// #include <Model/Model.hpp>
#include <Model/CaptureModel.hpp>

#include <UI/Panel/Base/Panel_Image.hpp>
#include <UI/Panel/CapturePanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <wx/gtk/button.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CapturePanel : public wxPanel {
  public:
    CapturePanel(wxWindow *parent, wxWindowID id,
                 std::unique_ptr<CaptureModel> &model);
    ~CapturePanel();

  private:
    const PanelID panel_id = PANEL_CAPTURE;
    const PanelID next_panel_id = PANEL_ROI;

    std::unique_ptr<CaptureModel> model;

    CaptureButtonPanel *button_panel;
    BaseImagePanel *img_bitmap;

    ButtonExit *exit_Button;

    TitleText *titleText;
    StatusText *statusText;

    wxBoxSizer *title_Sizer;
    wxBoxSizer *main_sizer;

    void OnLoadButton(ButtonWState *button);
    void OnCaptureButton(ButtonWState *button);
    void OnToggleCameraButton(ButtonWState *button);
    void OnChangePanelButton(wxButton *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnLoadImage(wxCommandEvent &e);
    // void OnChangePanel(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};