#include <Utils/Config/AppConfig.hpp>

AppConfig::AppConfig() {
    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() +
                            wxFileName::GetPathSeparator() + "config.ini";

    if (!wxFile::Exists(ini_filename)) {
        config = new wxFileConfig("", "", ini_filename);

        config->SetPath("/Camera_Panel");
        config->Write("Thread_Pool_Size", Default_Thread_Pool_Size);

        config->SetPath("/Camera_Parameter");
        config->Write("Camera_ID", Default_Camera_ID);
        config->Write("Camera_Width", Default_Camera_Width);
        config->Write("Camera_Height", Default_Camera_Height);
        config->Write("Camera_FPS", Default_Camera_FPS);

        config->SetPath("/Capture_Parameter");
        config->Write("Max_Frame_Count", Default_Max_Frame_Count);
        config->Write("Debug", Default_Debug);

        config->SetPath("/Load_Parameter");
        config->Write("Load_File_Name", Default_Load_File_Name);
        config->Write("Load_Dir_Location", Default_Load_File_Name);
        config->Write("Max_Frame", Default_Max_Frame);

        config->SetPath("/Detection_Parameter");
        config->Write("Max_Points", Default_Max_Points);
        config->Write("Threshold", Default_Threshold);

        config->SetPath("/Line_Selection_Parameter");
        config->Write("Radius", Default_Radius);
        config->Flush();
    } else {
        config = new wxFileConfig("", "", ini_filename);
    }
}

DetectionConfig AppConfig::GetDetectionConfig() {
    DetectionConfig detectionConfig;
    config->SetPath("/Detection_Parameter");
    config->Read("Max_Points", &detectionConfig.maxPoints, Default_Max_Points);
    config->Read("Threshold", &detectionConfig.threshold, Default_Threshold);
    return detectionConfig;
}

PanelConfig AppConfig::GetPanelConfig() {
    PanelConfig panelConfig;
    config->SetPath("/Camera_Panel");
    config->Read("Thread_Pool_Size", &panelConfig.Thread_Pool_Size,
                 Default_Thread_Pool_Size);
    return panelConfig;
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
    config->Read("Max_Frame_Count", &captureConfig.maxFrame,
                 Default_Max_Frame_Count);
    config->Read("Debug", &captureConfig.Debug, Default_Debug);
    return captureConfig;
}

LoadConfig AppConfig::GetLoadConfig() {
    LoadConfig loadConfig;
    loadConfig.path = GetLoadFileName();
    loadConfig.maxFrame = GetMaxLoadFrame();
    return loadConfig;
}

wxString AppConfig::GetLoadFileName() {
    wxString fileName;
    wxString dirLocation;
    config->SetPath("/Load_Parameter");
    config->Read("Load_File_Name", &fileName, Default_Load_File_Name);
    config->Read("Load_Dir_Location", &dirLocation, Default_Load_Dir_Location);
    if (fileName == "default" || dirLocation == "default") {
        return "";
    }
    return dirLocation + fileName;
}

int AppConfig::GetMaxLoadFrame() {
    int maxFrame;
    config->SetPath("/Load_Parameter");
    config->Read("Max_Frame", &maxFrame, Default_Max_Frame);
    return maxFrame;
}

int AppConfig::GetRadius() {
    int radius;
    config->SetPath("/Line_Selection_Parameter");
    config->Read("Radius", &radius, Default_Radius);
    return radius;
}

CannyConfig AppConfig::GetCannyConfig() {
    CannyConfig cannyConfig;
    config->SetPath("/Canny_Parameter");
    config->Read("Threshold1", &cannyConfig.threshold1, Default_Threshold1);
    config->Read("Threshold2", &cannyConfig.threshold2, Default_Threshold2);
    config->Read("Aperture_Size", &cannyConfig.apertureSize,
                 Default_Aperture_Size);
    config->Read("L2_Gradient", &cannyConfig.L2gradient, Default_L2_Gradient);
    return cannyConfig;
}

HoughConfig AppConfig::GetHoughConfig() {
    HoughConfig houghConfig;
    config->SetPath("/Hough_Parameter");
    config->Read("Rho", &houghConfig.rho, Default_Rho);
    config->Read("Theta", &houghConfig.theta, Default_Theta);
    config->Read("Threshold", &houghConfig.threshold, Default_Hough_Threshold);
    config->Read("Min_Line_Length", &houghConfig.minLineLength,
                 Default_Min_Line_Length);
    config->Read("Max_Line_Gap", &houghConfig.maxLineGap, Default_Max_Line_Gap);
    return houghConfig;
}

AppConfig::~AppConfig() { delete config; }