#pragma once

#include <Model/Model.hpp>

#include <UI/Panel/RoiPanel/Panel_Button.hpp>
#include <UI/Panel/RoiPanel/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <wx/wx.h>

class RoiPanel : public wxPanel {
  public:
    RoiPanel(wxWindow *parent, wxWindowID id, Model *model);
    ~RoiPanel();

    void Init();

  private:
    Model *model;

    RoiButtonPanel *button_panel;
    RoiImagePanel *img_bitmap;

    wxBoxSizer *main_sizer;

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnError(ErrorEvent &e);
    void OnLeftUp(wxMouseEvent &e);
    void OnLeftDown(wxMouseEvent &e);
    void OnMotion(wxMouseEvent &e);

    DECLARE_EVENT_TABLE()
};