#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include <Utils/Config/ConfigStruct.hpp>
#include <opencv2/core/cvdef.h>
#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/wx.h>

class AppConfig {
  public:
    AppConfig();
    ~AppConfig();

    wxString GetLoadFileName();

    PanelConfig GetPanelConfig();

    CameraConfig GetCameraConfig();

    CaptureConfig GetCaptureConfig();

    LoadConfig GetLoadConfig();

    DetectionConfig GetDetectionConfig();

    CannyConfig GetCannyConfig();

    HoughConfig GetHoughConfig();

    int GetMaxLoadFrame();

    int GetRadius();

  private:
    wxFileConfig *config;

    // Default Values
    // Camera Panel
    int Default_Thread_Pool_Size = 2;

    // Camera Parameter
    int Default_Camera_ID = 0;
    int Default_Camera_Width = 1280;
    int Default_Camera_Height = 960;
    int Default_Camera_FPS = 10;

    // Capture Parameter
    int Default_Max_Frame_Count = 10;
    bool Default_Debug = false;

    // Load Parameter
    wxString Default_Load_File_Name = "default";
    wxString Default_Load_Dir_Location = "default";
    int Default_Max_Frame = 10;

    // Detection Parameter
    int Default_Max_Points = 1000;
    double Default_Threshold = 2.0;

    // Line Selection Parameter
    int Default_Radius = 10;

    // Canny Parameter
    double Default_Threshold1 = 50.0;
    double Default_Threshold2 = 150.0;
    int Default_Aperture_Size = 3;
    bool Default_L2_Gradient = false;

    // HoughLine Parameter
    double Default_Rho = 1.0;
    double Default_Theta = CV_PI / 180;
    int Default_Hough_Threshold = 50;
    double Default_Min_Line_Length = 25;
    double Default_Max_Line_Gap = 10;
};

#endif