#include <Utils/Config/AppConfig.hpp>

AppConfig::AppConfig() {
    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() +
                            wxFileName::GetPathSeparator() + "SCPConfig.ini";

    if (!wxFile::Exists(ini_filename)) {
        config = new wxFileConfig("", "", ini_filename);

        config->SetPath("/Camera_Panel");
        config->Write("Thread_Pool_Size", Default_Thread_Pool_Size);

        config->SetPath("/Camera_Parameter");
        config->Write("Camera_ID", Default_Camera_ID);
        config->Write("Camera_Width", Default_Camera_Width);
        config->Write("Camera_Height", Default_Camera_Height);
        config->Write("Camera_FPS", Default_Camera_FPS);

        config->SetPath("/Sensor_Parameter");
        config->Write("Sensor_Width", Default_Sensor_Width);
        config->Write("Sensor_Focal_Length", Default_Sensor_Focal_Length);
        config->Write("Object_Width", Default_Object_Width);

        config->SetPath("/Capture_Parameter");
        config->Write("Max_Frame_Count", Default_Max_Frame_Count);
        config->Write("Debug", Default_Debug);

        config->SetPath("/Load_Parameter");
        config->Write("Load_File_Name", Default_Load_File_Name);
        config->Write("Load_Dir_Location", Default_Load_File_Name);
        config->Write("Max_Frame", Default_Max_Frame);

        config->SetPath("/Line_Selection_Parameter");
        config->Write("Radius", Default_Radius);

        config->SetPath("/Canny_Parameter");
        config->Write("Threshold1", Default_Threshold1);
        config->Write("Threshold2", Default_Threshold2);
        config->Write("ApertureSize", Default_Aperture_Size);
        config->Write("L2gradient", Default_L2_Gradient);

        config->SetPath("/Hough_Parameter");
        config->Write("Rho", Default_Rho);
        config->Write("Theta", Default_Theta);
        config->Write("Threshold", Default_Threshold);
        config->Write("MinLineLength", Default_Min_Line_Length);
        config->Write("MaxLineGap", Default_Max_Line_Gap);

        config->SetPath("/Optical_Flow_Parameter");
        config->Write("Max_Corners", Default_Max_Corners);
        config->Write("Quality_Level", Default_Quality_Level);
        config->Write("Min_Distance", Default_Min_Distance);
        config->Write("Block_Size", Default_Block_Size);
        config->Write("Use_Harris_Detector", Default_Use_Harris_Detector);
        config->Write("K", Default_K);
        config->Write("Min_Point_Distance", Default_Min_Point_Distance);
        config->Write("Threshold", Default_Threshold);

        config->SetPath("/HSV_Blue_Range_Parameter");
        config->Write("Hue_Min", Default_Hue_Blue_Low);
        config->Write("Hue_Max", Default_Hue_Blue_High);
        config->Write("Saturation_Min", Default_Sat_Blue_Low);
        config->Write("Saturation_Max", Default_Sat_Blue_High);
        config->Write("Value_Min", Default_Val_Blue_Low);
        config->Write("Value_Max", Default_Val_Blue_High);

        config->SetPath("/HSV_Yellow_Range_Parameter");
        config->Write("Hue_Min", Default_Hue_Yellow_Low);
        config->Write("Hue_Max", Default_Hue_Yellow_High);
        config->Write("Saturation_Min", Default_Sat_Yellow_Low);
        config->Write("Saturation_Max", Default_Sat_Yellow_High);
        config->Write("Value_Min", Default_Val_Yellow_Low);
        config->Write("Value_Max", Default_Val_Yellow_High);

        config->Flush();
    } else {
        config = new wxFileConfig("", "", ini_filename);
    }
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

SensorConfig AppConfig::GetSensorConfig() {
    SensorConfig sensorConfig;
    config->SetPath("/Sensor_Parameter");
    config->Read("Sensor_Width", &sensorConfig.SensorWidth,
                 Default_Sensor_Width);
    config->Read("Sensor_Focal_Length", &sensorConfig.SensorFocalLength,
                 Default_Sensor_Focal_Length);
    config->Read("Object_Width", &sensorConfig.ObjectWidth,
                 Default_Object_Width);
    return sensorConfig;
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

OpticalFlowConfig AppConfig::GetOpticalFlowConfig() {
    OpticalFlowConfig opticalFlowConfig;
    config->SetPath("/Optical_Flow_Parameter");
    config->Read("Max_Corners", &opticalFlowConfig.maxCorners,
                 Default_Max_Corners);
    config->Read("Quality_Level", &opticalFlowConfig.qualityLevel,
                 Default_Quality_Level);
    config->Read("Min_Distance", &opticalFlowConfig.minDistance,
                 Default_Min_Distance);
    config->Read("Block_Size", &opticalFlowConfig.blockSize,
                 Default_Block_Size);
    config->Read("Use_Harris_Detector", &opticalFlowConfig.useHarrisDetector,
                 Default_Use_Harris_Detector);
    config->Read("K", &opticalFlowConfig.k, Default_K);
    config->Read("Min_Point_Distance", &opticalFlowConfig.minPointDistance,
                 Default_Min_Point_Distance);
    config->Read("Threshold", &opticalFlowConfig.threshold, Default_Threshold);
    return opticalFlowConfig;
}

std::pair<cv::Scalar, cv::Scalar> AppConfig::GetBlueRange() {
    cv::Scalar lowerBound, upperBound;

    int hueMin, hueMax, satMin, satMax, valMin, valMax;
    config->SetPath("/HSV_Blue_Range_Parameter");
    config->Read("Hue_Min", &hueMin, Default_Hue_Blue_Low);
    config->Read("Hue_Max", &hueMax, Default_Hue_Blue_High);
    config->Read("Saturation_Min", &satMin, Default_Sat_Blue_Low);
    config->Read("Saturation_Max", &satMax, Default_Sat_Blue_High);
    config->Read("Value_Min", &valMin, Default_Val_Blue_Low);
    config->Read("Value_Max", &valMax, Default_Val_Blue_High);

    if (hueMin < 0 || hueMin > 255 || hueMax < 0 || hueMax > 255 ||
        satMin < 0 || satMin > 255 || satMax < 0 || satMax > 255 ||
        valMin < 0 || valMin > 255 || valMax < 0 || valMax > 255) {
        throw std::invalid_argument("HSV Blue out of range");
    }

    if (hueMin > hueMax) {
        throw std::invalid_argument("Hue min (blue) is greater than hue max");
    }

    if (satMin > satMax) {
        throw std::invalid_argument(
            "Saturation min (blue) is greater than max");
    }

    if (valMin > valMax) {
        throw std::invalid_argument("Value min (blue) is greater than max");
    }

    lowerBound = cv::Scalar(hueMin, satMin, valMin);
    upperBound = cv::Scalar(hueMax, satMax, valMax);
    return std::make_pair(lowerBound, upperBound);
}

void AppConfig::SetBlueRange(std::pair<cv::Scalar, cv::Scalar> range) {
    cv::Scalar lowerBound = range.first;
    cv::Scalar upperBound = range.second;

    int hueMin = lowerBound[0];
    int hueMax = upperBound[0];
    int satMin = lowerBound[1];
    int satMax = upperBound[1];
    int valMin = lowerBound[2];
    int valMax = upperBound[2];

    config->SetPath("/HSV_Blue_Range_Parameter");
    config->Write("Hue_Min", hueMin);
    config->Write("Hue_Max", hueMax);
    config->Write("Saturation_Min", satMin);
    config->Write("Saturation_Max", satMax);
    config->Write("Value_Min", valMin);
    config->Write("Value_Max", valMax);
}

void AppConfig::ResetBlueRange() {
    SetBlueRange(
        std::make_pair(cv::Scalar(Default_Hue_Blue_Low, Default_Sat_Blue_Low,
                                  Default_Val_Blue_Low),
                       cv::Scalar(Default_Hue_Blue_High, Default_Sat_Blue_High,
                                  Default_Val_Blue_High)));
}

std::pair<cv::Scalar, cv::Scalar> AppConfig::GetYellowRange() {
    cv::Scalar lowerBound, upperBound;

    int hueMin, hueMax, satMin, satMax, valMin, valMax;
    config->SetPath("/HSV_Yellow_Range_Parameter");
    config->Read("Hue_Min", &hueMin, Default_Hue_Yellow_Low);
    config->Read("Hue_Max", &hueMax, Default_Hue_Yellow_High);
    config->Read("Saturation_Min", &satMin, Default_Sat_Yellow_Low);
    config->Read("Saturation_Max", &satMax, Default_Sat_Yellow_High);
    config->Read("Value_Min", &valMin, Default_Val_Yellow_Low);
    config->Read("Value_Max", &valMax, Default_Val_Yellow_High);

    if (hueMin < 0 || hueMin > 255 || hueMax < 0 || hueMax > 255 ||
        satMin < 0 || satMin > 255 || satMax < 0 || satMax > 255 ||
        valMin < 0 || valMin > 255 || valMax < 0 || valMax > 255) {
        throw std::invalid_argument("HSV Yellow out of range");
    }

    if (hueMin > hueMax) {
        throw std::invalid_argument("Hue min (yellow) is greater than hue max");
    }

    if (satMin > satMax) {
        throw std::invalid_argument(
            "Saturation min (yellow) is greater than max");
    }

    if (valMin > valMax) {
        throw std::invalid_argument("Value min (yellow) is greater than max");
    }

    lowerBound = cv::Scalar(hueMin, satMin, valMin);
    upperBound = cv::Scalar(hueMax, satMax, valMax);
    return std::make_pair(lowerBound, upperBound);
}

void AppConfig::SetYellowRange(std::pair<cv::Scalar, cv::Scalar> range) {
    cv::Scalar lowerBound = range.first;
    cv::Scalar upperBound = range.second;

    int hueMin = lowerBound[0];
    int hueMax = upperBound[0];
    int satMin = lowerBound[1];
    int satMax = upperBound[1];
    int valMin = lowerBound[2];
    int valMax = upperBound[2];

    config->SetPath("/HSV_Yellow_Range_Parameter");
    config->Write("Hue_Min", hueMin);
    config->Write("Hue_Max", hueMax);
    config->Write("Saturation_Min", satMin);
    config->Write("Saturation_Max", satMax);
    config->Write("Value_Min", valMin);
    config->Write("Value_Max", valMax);
}

void AppConfig::ResetYellowRange() {
    SetYellowRange(std::make_pair(
        cv::Scalar(Default_Hue_Yellow_Low, Default_Sat_Yellow_Low,
                   Default_Val_Yellow_Low),
        cv::Scalar(Default_Hue_Yellow_High, Default_Sat_Yellow_High,
                   Default_Val_Yellow_High)));
}

AppConfig::~AppConfig() { delete config; }