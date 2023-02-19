#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include <Utils/Config/ConfigStruct.hpp>
#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/wx.h>

class AppConfig {
  public:
    AppConfig();
    ~AppConfig();

    int GetCameraPanelRefreshRate();

    int GetResultPanelRefreshRate();

    wxString GetLoadFileName();

    CameraConfig GetCameraConfig();

    CaptureConfig GetCaptureConfig();

  private:
    wxFileConfig *config;

    // Default Values
    // Camera Panel
    int Default_Camera_Panel_Refresh_Rate = 33;

    // Result Panel
    int Default_Result_Panel_Refresh_Rate = 500;

    // Camera Parameter
    int Default_Camera_ID = 0;
    int Default_Camera_Width = 640;
    int Default_Camera_Height = 480;
    int Default_Camera_FPS = 30;

    // Capture Parameter
    int Default_Max_Frame_Count = 10;
    int Default_Frame_Interval = 100;
    int Default_Thread_Pool_Size = 2;
};

#endif