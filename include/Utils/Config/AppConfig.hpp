#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include <Utils/Config/ConfigStruct.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/types.hpp>
#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/wx.h>

class AppConfig {
  public:
    AppConfig();
    ~AppConfig();

    void ResetConfig();
    void SaveConfig(const SettingsModel &model);

    ModelConfig GetModelConfig();
    void SetModelConfig(ModelConfig config);
    void ResetModelConfig();

    PreviewConfig GetPreviewConfig();
    void SetPreviewConfig(PreviewConfig config);
    void ResetPreviewConfig();

    CameraConfig GetCameraConfig();
    void SetCameraConfig(CameraConfig config);
    void ResetCameraConfig();

    CaptureConfig GetCaptureConfig();
    void SetCaptureConfig(CaptureConfig config);
    void ResetCaptureConfig();

    LoadConfig GetLoadConfig();
    void SetLoadConfig(LoadConfig config);
    void ResetLoadConfig();

    OpticalFlowConfig GetOpticalFlowConfig();
    void SetOpticalFlowConfig(OpticalFlowConfig config);
    void ResetOpticalFlowConfig();

    SensorConfig GetSensorConfig();
    void SetSensorConfig(SensorConfig config);
    void ResetSensorConfig();

    MeasurementConfig GetMeasurementConfig();
    void SetMeasurementConfig(MeasurementConfig config);
    void ResetMeasurementConfig();

    HSVRangeConfig GetBlueRange();
    void SetBlueRange(HSVRangeConfig range);
    void ResetBlueRange();

    HSVRangeConfig GetYellowRange();
    void SetYellowRange(HSVRangeConfig range);
    void ResetYellowRange();

    RansacConfig GetRansacConfig();
    void SetRansacConfig(RansacConfig config);
    void ResetRansacConfig();

    SettingsModel GetSettingsModel();

  private:
    wxFileConfig *config;

    // Default Values

    // Model Config
    int Default_Thread_Pool_Size = 2;

    // Preview Config
    int Default_Preview_Width = 640;
    int Default_Preview_Height = 480;

    // Camera Parameter
    int Default_Camera_ID = 0;
    int Default_Camera_Width = 1280;
    int Default_Camera_Height = 960;
    int Default_Camera_FPS = 10;

    // Sensor Parameter
    double Default_Sensor_Width = 3.68;
    double Default_Sensor_Focal_Length = 3.04;

    // Measurement Parameter
    double Default_Object_Width = 3500.0;

    // Capture Parameter
    int Default_Max_Frame_Count = 10;
    bool Default_Debug = false;

    // Load Parameter
    int Default_Max_Frame = 10;

    // Detection Parameter
    int Default_Max_Points = 1000;

    // Line Selection Parameter
    int Default_Radius = 10;

    // Optical Flow Parameter
    int Default_Max_Corners = 1000;
    double Default_Quality_Level = 0.05;
    double Default_Min_Distance = 7;
    int Default_Block_Size = 3;
    bool Default_Use_Harris_Detector = false;
    double Default_K = 0.04;
    double Default_Min_Point_Distance = 0.2;
    double Default_Threshold = 2.0;

    // HSV Blue Range Parameter
    int Default_Hue_Blue_Low = 100;
    int Default_Hue_Blue_High = 130;

    int Default_Sat_Blue_Low = 100;
    int Default_Sat_Blue_High = 255;

    int Default_Val_Blue_Low = 100;
    int Default_Val_Blue_High = 255;

    // HSV Yellow Range Parameter
    int Default_Hue_Yellow_Low = 20;
    int Default_Hue_Yellow_High = 35;

    int Default_Sat_Yellow_Low = 100;
    int Default_Sat_Yellow_High = 255;

    int Default_Val_Yellow_Low = 100;
    int Default_Val_Yellow_High = 255;

    // RANSAC Parameter
    double Default_RANSAC_Threshold = 6;
    int Default_RANSAC_Min_Points = 50;
    int Default_RANSAC_Max_Iterations = 500;
};

#endif