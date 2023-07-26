#pragma once

#include "Controller/CaptureController.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include <Event/Event_Replay.hpp>

#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Button/Button_Exit.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/RoiPanel/Panel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"

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
    CapturePanel(wxWindow *parent, wxWindowID id, CPCPtr &controller);
    ~CapturePanel();

  private:
    const PanelID panel_id = PANEL_CAPTURE;

    CPCPtr controller;

    CaptureButtonPanel *button_panel;
    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    wxBoxSizer *main_sizer;

    void OnLoadButton(ButtonWState *button);
    void OnCaptureButton(wxButton *button);
    void OnToggleCameraButton(BitmapButtonT2 *button);
    void OnChangePanelButton(wxButton *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnLoadImage(wxCommandEvent &e);
    void OnUpdateState(UpdateStateEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);
    void OnReplay(wxCommandEvent &e);
    void OnShow(wxShowEvent &e);
    // void OnChangePanel(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};