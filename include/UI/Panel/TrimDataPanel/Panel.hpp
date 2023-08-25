#pragma once

#include "Controller/ManualCalibrationController.hpp"
#include "Controller/TrimDataController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/TrimDataPanel/Panel_Button.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Common/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/event.h>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimDataPanel : public wxPanel {
  public:
    TrimDataPanel(wxWindow *parent, wxWindowID id, TDCPtr &controller);
    ~TrimDataPanel();

  private:
    const PanelID panel_id = PANEL_TRIM_DATA;

    TDCPtr controller;

    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    TrimDataPanelButton *button_panel;

    wxBoxSizer *main_sizer;

    void ToggleTrimDataButtonHandler(BitmapButtonT2 *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);
    void OnUpdateState(UpdateStateEvent &e);
    void OnReplay(wxCommandEvent &e);
    void OnRequestUpdateState(wxCommandEvent &e);
    void OnShow(wxShowEvent &e);

    DECLARE_EVENT_TABLE()
};