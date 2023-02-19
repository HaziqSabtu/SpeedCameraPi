#include <Utils/Config/AppConfig.hpp>

AppConfig::AppConfig() {
    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() +
                            wxFileName::GetPathSeparator() + "config.ini";

    if (!wxFile::Exists(ini_filename)) {
        config = new wxFileConfig("", "", ini_filename);

        config->SetPath("/Camera_Panel");
        config->Write("Panel_Refresh_Rate", Default_Camera_Panel_Refresh_Rate);

        config->SetPath("/Result_Panel");
        config->Write("Panel_Refresh_Rate", Default_Result_Panel_Refresh_Rate);
        config->SetPath("/Camera_Parameter");
        config->Write("Camera_ID", Default_Camera_ID);
        config->Write("Camera_Width", Default_Camera_Width);
        config->Write("Camera_Height", Default_Camera_Height);
        config->Write("Camera_FPS", Default_Camera_FPS);

        config->SetPath("/Capture_Parameter");
        config->Write("Max_Frame_Count", Default_Max_Frame_Count);
        config->Write("Frame_Interval", Default_Frame_Interval);
        config->Write("Thread_Pool_Size", Default_Thread_Pool_Size);
        config->SetPath("/Select_Line_Panel");
        config->Write("Panel_Refresh_Rate", 33);

        config->SetPath("/Load_Parameter");
        config->Write("Load_File_Name", "default");
        config->Write("Load_Dir_Location", "default");
        config->Flush();
    } else {
        config = new wxFileConfig("", "", ini_filename);
    }
}

CameraConfig AppConfig::GetCameraConfig() {
    CameraConfig cameraConfig;
    config->SetPath("/Camera_Parameter");
    config->Read("Camera_ID", &cameraConfig.Camera_ID, Default_Camera_ID);
    config->Read("Camera_Width", &cameraConfig.Camera_Width,
                 Default_Camera_Width);
    config->Read("Camera_Height", &cameraConfig.Camera_Height,
                 Default_Camera_Height);
    config->Read("Camera_FPS", &cameraConfig.Camera_FPS, Default_Camera_FPS);
    return cameraConfig;
}

CaptureConfig AppConfig::GetCaptureConfig() {
    CaptureConfig captureConfig;
    config->SetPath("/Capture_Parameter");
    config->Read("Max_Frame_Count", &captureConfig.Max_Frame_Count,
                 Default_Max_Frame_Count);
    config->Read("Frame_Interval", &captureConfig.Frame_Interval,
                 Default_Frame_Interval);
    config->Read("Thread_Pool_Size", &captureConfig.Thread_Pool_Size,
                 Default_Thread_Pool_Size);
    return captureConfig;
}

int AppConfig::GetCameraPanelRefreshRate() {
    int refreshRate;
    config->SetPath("/Camera_Panel");
    config->Read("Panel_Refresh_Rate", &refreshRate,
                 Default_Camera_Panel_Refresh_Rate);
    return refreshRate;
}

int AppConfig::GetResultPanelRefreshRate() {
    int refreshRate;
    config->SetPath("/Result_Panel");
    config->Read("Panel_Refresh_Rate", &refreshRate,
                 Default_Result_Panel_Refresh_Rate);
    return refreshRate;
}

wxString AppConfig::GetLoadFileName() {
    wxString fileName;
    wxString dirLocation;
    config->SetPath("/Load_Parameter");
    config->Read("Load_File_Name", &fileName, "default");
    config->Read("Load_Dir_Location", &dirLocation, "default");
    if (fileName == "default" || dirLocation == "default") {
        return "";
    }
    return dirLocation + fileName;
}

AppConfig::~AppConfig() { delete config; }