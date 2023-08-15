#pragma once

#include "Controller/ManualCalibrationController.hpp"
#include "Controller/ResultController.hpp"
#include "Controller/RoiController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Common/Panel_Image.hpp>
#include <UI/Panel/ResultPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPanel : public wxPanel {
  public:
    ResultPanel(wxWindow *parent, wxWindowID id, RSCPtr &controller);
    ~ResultPanel();

  private:
    const PanelID panel_id = PANEL_RESULT;

    RSCPtr controller;

    BaseImagePanel *img_bitmap;

    TitlePanel *title_panel;
    StatusPanel *status_panel;

    ResultPanelButton *button_panel;

    wxBoxSizer *main_sizer;

    void ToggleReplayButtonHandler(BitmapButtonT2 *button);
    void ToggleBoxButtonHandler(BitmapButtonT2 *button);
    void ToggleLinesButtonHandler(BitmapButtonT2 *button);
    void ToggleLanesButtonHandler(BitmapButtonT2 *button);

    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnButton(wxCommandEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);
    void OnUpdateState(UpdateStateEvent &e);
    void OnProcessImage(wxCommandEvent &e);
    void OnShow(wxShowEvent &e);

    DECLARE_EVENT_TABLE()
};