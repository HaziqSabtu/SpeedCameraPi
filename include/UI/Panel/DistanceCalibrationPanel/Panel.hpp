#pragma once

#include "Controller/DistanceCalibrationController.hpp"
#include "Model/SessionData.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include <UI/Panel/DistanceCalibrationPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class DistanceCalibrationPanel : public BasePanelWithTouch {
  public:
    DistanceCalibrationPanel(wxWindow *parent, wxWindowID id,
                             DCCPtr controller);
    ~DistanceCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_DISTANCE_CALIBRATION;

    DCCPtr controller;

    void TogglePreviewButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnPreviewCapture(wxCommandEvent &e);
    void OnPreviewCamera(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};