#pragma once

#include "Controller/CaptureController.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include <Event/Event_Replay.hpp>

#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/RoiPanel/Panel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"

#include <UI/Panel/CapturePanel/Panel_Button.hpp>
#include <UI/Panel/Common/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <wx/gtk/button.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CapturePanel : public BasePanel {
  public:
    CapturePanel(wxWindow *parent, wxWindowID id, CPCPtr controller);
    ~CapturePanel();

  private:
    const PanelID panel_id = PANEL_CAPTURE;

    CPCPtr controller;

    void LoadButtonHandler();
    void ToggleCameraButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnLoadImage(wxCommandEvent &e);
    void OnPreviewCapture(wxCommandEvent &e);
    void OnPreviewCamera(wxCommandEvent &e);
    void OnSaveData(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};