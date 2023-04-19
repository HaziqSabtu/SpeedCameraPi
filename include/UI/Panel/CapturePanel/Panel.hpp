#pragma once

#include <Model/Model.hpp>

#include <UI/Panel/Base/Panel_Image.hpp>
#include <UI/Panel/CapturePanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <wx/wx.h>

class CapturePanel : public wxPanel {
  public:
    CapturePanel(wxWindow *parent, wxWindowID id, Model *model);
    ~CapturePanel();

  private:
    Model *model;

    CaptureButtonPanel *button_panel;
    BaseImagePanel *img_bitmap;

    wxBoxSizer *main_sizer;

    void OnLoadButton(ButtonWState *button);
    void OnCaptureButton(ButtonWState *button);
    void OnToggleCameraButton(ButtonWState *button);
    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void onLoadImage(wxCommandEvent &e);
    void OnError(ErrorEvent &e);

    DECLARE_EVENT_TABLE()
};