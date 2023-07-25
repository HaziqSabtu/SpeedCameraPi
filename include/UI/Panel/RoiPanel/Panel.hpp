#pragma once

#include "Model/RoiModel.hpp"

#include <UI/Panel/RoiPanel/Panel_Button.hpp>
#include <UI/Panel/RoiPanel/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <wx/wx.h>

class RoiPanel : public wxPanel {
  public:
    RoiPanel(wxWindow *parent, wxWindowID id, std::unique_ptr<RoiModel> &model);
    ~RoiPanel();

    void Init();

  private:
    std::unique_ptr<RoiModel> model;

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