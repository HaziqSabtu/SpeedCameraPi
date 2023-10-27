#pragma once

#include <UI/Panel/SettingsPanel/SettingsCamera.hpp>
#include <UI/Panel/SettingsPanel/SettingsCapture.hpp>
#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>
#include <UI/Panel/SettingsPanel/SettingsHSV.hpp>
#include <UI/Panel/SettingsPanel/SettingsMeasurement.hpp>
#include <UI/Panel/SettingsPanel/SettingsModel.hpp>
#include <UI/Panel/SettingsPanel/SettingsOpticalFlow.hpp>
#include <UI/Panel/SettingsPanel/SettingsPreview.hpp>
#include <UI/Panel/SettingsPanel/SettingsRansac.hpp>
#include <UI/Panel/SettingsPanel/SettingsSensor.hpp>
#include <UI/Panel/SettingsPanel/SettingsThreads.hpp>

/**
 * @brief The settings panel
 * @image html settingspanel.png
 * @image latex settingspanel.png
 */
class SettingsScrollPanel : public wxScrolledWindow {
  public:
    SettingsScrollPanel(wxWindow *parent);

    SettingsModel getSettingsModel();
    void setSettingsModel(const SettingsModel &settingsModel);

  private:
    SettingsModelComponent *settingsModelComponent;
    SettingsCameraComponent *settingsCameraComponent;
    SettingsCaptureComponent *settingsCaptureComponent;
    SettingsOptFlowComponent *settingsOptFlowComponent;
    SettingsSensorComponent *settingsSensorComponent;
    SettingsMeasurementComponent *settingsMeasurementComponent;
    SettingsPreviewComponent *settingsPreviewComponent;
    SettingsRansacComponent *settingsRansacComponent;
    SettingsBlueHSVComponent *settingsBlueHSVComponent;
    SettingsYellowHSVComponent *settingsYellowHSVComponent;
    SettingsThreadsComponent *settingsThreadsComponent;
};
