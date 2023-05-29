#pragma once

#include "UI/Panel/RoiPanel/Panel.hpp"
// #include <Model/Model.hpp>
#include <Model/CaptureModel.hpp>

#include <UI/Panel/Base/Panel_Image.hpp>
#include <UI/Panel/CapturePanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <wx/gtk/button.h>
#include <wx/wx.h>

class CapturePanel : public wxPanel {
  public:
    CapturePanel(wxWindow *parent, wxWindowID id,
                 std::unique_ptr<CaptureModel> &model);
    ~CapturePanel();

    void setNextPanel(RoiPanel *panel);

  private:
    std::unique_ptr<CaptureModel> model;

    CaptureButtonPanel *button_panel;
    BaseImagePanel *img_bitmap;

    wxBoxSizer *main_sizer;

    RoiPanel *nextPanel;

    void OnLoadButton(ButtonWState *button);
    void OnCaptureButton(ButtonWState *button);
    void OnToggleCameraButton(ButtonWState *button);
    void OnChangePanelButton(wxButton *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnLoadImage(wxCommandEvent &e);
    void OnChangePanel(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};