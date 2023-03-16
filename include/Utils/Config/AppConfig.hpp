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

    wxString GetLoadFileName();

    PanelConfig GetPanelConfig();

    CameraConfig GetCameraConfig();

    CaptureConfig GetCaptureConfig();

    LoadConfig GetLoadConfig();

    int GetMaxLoadFrame();

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
};

#endif