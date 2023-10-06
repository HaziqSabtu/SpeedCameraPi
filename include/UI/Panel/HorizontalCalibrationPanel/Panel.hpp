#pragma once

#include "Controller/HorizontalCalibrationController.hpp"
#include "Model/SessionData.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include <UI/Panel/HorizontalCalibrationPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class HorizontalCalibrationPanel : public BasePanelWithTouch {
  public:
    HorizontalCalibrationPanel(wxWindow *parent, wxWindowID id,
                               HCCPtr controller);
    ~HorizontalCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_HORIZONTAL_CALIBRATION;

    HCCPtr controller;

    // void doPostLeftDown() override;

    void TogglePreviewButtonHandler(BitmapButtonT2 *button);
    void TogglePreviewCaptureButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationCaptureButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnPreviewCapture(wxCommandEvent &e);
    void OnPreviewCamera(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};