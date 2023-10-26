#include "Utils/Config/ConfigStruct.hpp"
#include <Utils/Config/AppConfig.hpp>

/**
 * @brief Construct a new App Config:: App Config object
 *
 */
AppConfig::AppConfig() {
    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() +
                            wxFileName::GetPathSeparator() + "SCPConfig.ini";

    if (!wxFile::Exists(ini_filename)) {
        config = new wxFileConfig("", "", ini_filename);

        config->SetPath("/Model_Parameter");
        config->Write("Pool_Size", Default_Thread_Pool_Size);

        config->SetPath("/Preview_Config");
        config->Write("Preview_Width", Default_Preview_Width);
        config->Write("Preview_Height", Default_Preview_Height);

        config->SetPath("/Camera_Parameter");
        config->Write("Camera_ID", Default_Camera_ID);
        config->Write("Camera_Width", Default_Camera_Width);
        config->Write("Camera_Height", Default_Camera_Height);
        config->Write("Camera_FPS", Default_Camera_FPS);

        config->SetPath("/Sensor_Parameter");
        config->Write("Sensor_Width", Default_Sensor_Width);
        config->Write("Sensor_Focal_Length", Default_Sensor_Focal_Length);

        config->SetPath("/Measurement_Parameter");
        config->Write("Object_Width", Default_Object_Width);
        config->Write("Object_Height", Default_Object_Height);

        config->SetPath("/Capture_Parameter");
        config->Write("Max_Frame_Count", Default_Max_Frame_Count);
        config->Write("Debug_Show_Image", Default_DebugShowImage);
        config->Write("Debug_Save", Default_DebugSave);

        config->SetPath("/Line_Selection_Parameter");
        config->Write("Radius", Default_Radius);

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

        config->SetPath("/Ransac_Parameter");
        config->Write("Distance_Threshold", Default_RANSAC_Threshold);
        config->Write("Max_Iterations", Default_RANSAC_Max_Iterations);
        config->Write("Min Points", Default_RANSAC_Min_Points);

        config->SetPath("/Threads_Parameter");
        config->Write("Auto_Manual_Calibration", Default_AutoManualCalibration);
        config->Write("Auto_Calibration", Default_AutoCalibration);
        config->Write("Auto_Roi", Default_AutoRoi);
        config->Write("Auto_Result", Default_AutoResult);

        config->Flush();
    } else {
        config = new wxFileConfig("", "", ini_filename);
    }
}

/**
 * @brief Get the ModelConfig object
 *
 * @return ModelConfig
 */
ModelConfig AppConfig::GetModelConfig() {
    ModelConfig modelConfig;
    config->SetPath("/Model_Parameter");
    config->Read("Pool_Size", &modelConfig.Pool_Size, Default_Thread_Pool_Size);
    return modelConfig;
}

/**
 * @brief Set the ModelConfig object
 *
 * @param modelConfig
 */
void AppConfig::SetModelConfig(ModelConfig modelConfig) {
    int poolSize = modelConfig.Pool_Size;

    config->SetPath("/Model_Parameter");
    config->Write("Pool_Size", poolSize);
}

/**
 * @brief Reset the ModelConfig object to default
 *
 */
void AppConfig::ResetModelConfig() {
    ModelConfig modelConfig;
    modelConfig.Pool_Size = Default_Thread_Pool_Size;

    SetModelConfig(modelConfig);
}

/**
 * @brief Get the PreviewConfig object
 *
 * @return PreviewConfig
 */
PreviewConfig AppConfig::GetPreviewConfig() {
    PreviewConfig previewConfig;
    config->SetPath("/Preview_Config");
    config->Read("Preview_Width", &previewConfig.width, Default_Preview_Width);
    config->Read("Preview_Height", &previewConfig.height,
                 Default_Preview_Height);
    return previewConfig;
}

/**
 * @brief Set the PreviewConfig object
 *
 * @param previewConfig
 */
void AppConfig::SetPreviewConfig(PreviewConfig previewConfig) {
    int width = previewConfig.width;
    int height = previewConfig.height;

    config->SetPath("/Preview_Config");
    config->Write("Preview_Width", width);
    config->Write("Preview_Height", height);
}

/**
 * @brief Reset the PreviewConfig object to default
 *
 */
void AppConfig::ResetPreviewConfig() {
    PreviewConfig previewConfig;
    previewConfig.width = Default_Preview_Width;
    previewConfig.height = Default_Preview_Height;

    SetPreviewConfig(previewConfig);
}

/**
 * @brief Get the CameraConfig object
 *
 * @return CameraConfig
 */
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

/**
 * @brief Set the CameraConfig object
 *
 * @param cameraConfig
 */
void AppConfig::SetCameraConfig(CameraConfig cameraConfig) {
    int cameraID = cameraConfig.Camera_ID;
    int cameraWidth = cameraConfig.Camera_Width;
    int cameraHeight = cameraConfig.Camera_Height;
    int cameraFPS = cameraConfig.Camera_FPS;

    config->SetPath("/Camera_Parameter");
    config->Write("Camera_ID", cameraID);
    config->Write("Camera_Width", cameraWidth);
    config->Write("Camera_Height", cameraHeight);
    config->Write("Camera_FPS", cameraFPS);
}

/**
 * @brief Reset the CameraConfig object to default
 *
 */
void AppConfig::ResetCameraConfig() {
    CameraConfig cameraConfig;
    cameraConfig.Camera_ID = Default_Camera_ID;
    cameraConfig.Camera_Width = Default_Camera_Width;
    cameraConfig.Camera_Height = Default_Camera_Height;
    cameraConfig.Camera_FPS = Default_Camera_FPS;

    SetCameraConfig(cameraConfig);
}

/**
 * @brief Get the SensorConfig object
 *
 * @return SensorConfig
 */
SensorConfig AppConfig::GetSensorConfig() {
    SensorConfig sensorConfig;
    config->SetPath("/Sensor_Parameter");
    config->Read("Sensor_Width", &sensorConfig.SensorWidth,
                 Default_Sensor_Width);
    config->Read("Sensor_Focal_Length", &sensorConfig.SensorFocalLength,
                 Default_Sensor_Focal_Length);
    return sensorConfig;
}

/**
 * @brief Set the SensorConfig object
 *
 * @param sensorConfig
 */
void AppConfig::SetSensorConfig(SensorConfig sensorConfig) {
    double sensorWidth = sensorConfig.SensorWidth;
    double sensorFocalLength = sensorConfig.SensorFocalLength;

    config->SetPath("/Sensor_Parameter");
    config->Write("Sensor_Width", sensorWidth);
    config->Write("Sensor_Focal_Length", sensorFocalLength);
}

/**
 * @brief Reset the SensorConfig object to default
 *
 */
void AppConfig::ResetSensorConfig() {
    SensorConfig sensorConfig;
    sensorConfig.SensorWidth = Default_Sensor_Width;
    sensorConfig.SensorFocalLength = Default_Sensor_Focal_Length;

    SetSensorConfig(sensorConfig);
}

/**
 * @brief Get the MeasurementConfig object
 *
 * @return MeasurementConfig
 */
MeasurementConfig AppConfig::GetMeasurementConfig() {
    MeasurementConfig measurementConfig;
    config->SetPath("/Measurement_Parameter");
    config->Read("Object_Width", &measurementConfig.ObjectWidth,
                 Default_Object_Width);
    config->Read("Object_Height", &measurementConfig.ObjectHeight,
                 Default_Object_Height);
    return measurementConfig;
}

/**
 * @brief Set the MeasurementConfig object
 *
 * @param measurementConfig
 */
void AppConfig::SetMeasurementConfig(MeasurementConfig measurementConfig) {
    double objectWidth = measurementConfig.ObjectWidth;
    double objectHeight = measurementConfig.ObjectHeight;

    config->SetPath("/Measurement_Parameter");
    config->Write("Object_Width", objectWidth);
    config->Write("Object_Height", objectHeight);
}

/**
 * @brief Reset the MeasurementConfig object to default
 *
 */
void AppConfig::ResetMeasurementConfig() {
    MeasurementConfig measurementConfig;
    measurementConfig.ObjectWidth = Default_Object_Width;
    measurementConfig.ObjectHeight = Default_Object_Height;

    SetMeasurementConfig(measurementConfig);
}

/**
 * @brief Get the CaptureConfig object
 *
 * @return CaptureConfig
 */
CaptureConfig AppConfig::GetCaptureConfig() {
    CaptureConfig captureConfig;
    config->SetPath("/Capture_Parameter");
    config->Read("Max_Frame_Count", &captureConfig.maxFrame,
                 Default_Max_Frame_Count);
    config->Read("Debug_Show_Image", &captureConfig.DebugShowImage,
                 Default_DebugShowImage);
    config->Read("Debug_Save", &captureConfig.DebugSave, Default_DebugSave);
    return captureConfig;
}

/**
 * @brief Set the CaptureConfig object
 *
 * @param captureConfig
 */
void AppConfig::SetCaptureConfig(CaptureConfig captureConfig) {
    int maxFrame = captureConfig.maxFrame;
    bool debug = captureConfig.DebugShowImage;

    config->SetPath("/Capture_Parameter");
    config->Write("Max_Frame_Count", maxFrame);
    config->Write("Debug_Show_Image", debug);
    config->Write("Debug_Save", captureConfig.DebugSave);
}

/**
 * @brief Reset the CaptureConfig object to default
 *
 */
void AppConfig::ResetCaptureConfig() {
    CaptureConfig captureConfig;
    captureConfig.maxFrame = Default_Max_Frame_Count;
    captureConfig.DebugShowImage = Default_DebugShowImage;
    captureConfig.DebugSave = Default_DebugSave;
    SetCaptureConfig(captureConfig);
}

/**
 * @brief Get the OpticalFlowConfig object
 *
 * @return OpticalFlowConfig
 */
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

/**
 * @brief Set the OpticalFlowConfig object
 *
 * @param opticalFlowConfig
 */
void AppConfig::SetOpticalFlowConfig(OpticalFlowConfig opticalFlowConfig) {
    int maxCorners = opticalFlowConfig.maxCorners;
    double qualityLevel = opticalFlowConfig.qualityLevel;
    double minDistance = opticalFlowConfig.minDistance;
    int blockSize = opticalFlowConfig.blockSize;
    bool useHarrisDetector = opticalFlowConfig.useHarrisDetector;
    double k = opticalFlowConfig.k;
    double minPointDistance = opticalFlowConfig.minPointDistance;
    double threshold = opticalFlowConfig.threshold;

    config->SetPath("/Optical_Flow_Parameter");
    config->Write("Max_Corners", maxCorners);
    config->Write("Quality_Level", qualityLevel);
    config->Write("Min_Distance", minDistance);
    config->Write("Block_Size", blockSize);
    config->Write("Use_Harris_Detector", useHarrisDetector);
    config->Write("K", k);
    config->Write("Min_Point_Distance", minPointDistance);
    config->Write("Threshold", threshold);
}

/**
 * @brief Reset the OpticalFlowConfig object to default
 *
 */
void AppConfig::ResetOpticalFlowConfig() {
    OpticalFlowConfig opticalFlowConfig;
    opticalFlowConfig.maxCorners = Default_Max_Corners;
    opticalFlowConfig.qualityLevel = Default_Quality_Level;
    opticalFlowConfig.minDistance = Default_Min_Distance;
    opticalFlowConfig.blockSize = Default_Block_Size;
    opticalFlowConfig.useHarrisDetector = Default_Use_Harris_Detector;
    opticalFlowConfig.k = Default_K;
    opticalFlowConfig.minPointDistance = Default_Min_Point_Distance;
    opticalFlowConfig.threshold = Default_Threshold;

    SetOpticalFlowConfig(opticalFlowConfig);
}

/**
 * @brief Get the HSVRangeConfig object
 *
 * @return HSVRangeConfig of blue
 */
HSVRangeConfig AppConfig::GetBlueRange() {
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

    HSVRangeConfig r;
    r.hueLower = hueMin;
    r.hueUpper = hueMax;
    r.saturationLower = satMin;
    r.saturationUpper = satMax;
    r.valueLower = valMin;
    r.valueUpper = valMax;
    return r;
}

/**
 * @brief Set the HSVRangeConfig of blue
 *
 * @param range
 */
void AppConfig::SetBlueRange(HSVRangeConfig range) {

    int hueMin = range.hueLower;
    int hueMax = range.hueUpper;
    int satMin = range.saturationLower;
    int satMax = range.saturationUpper;
    int valMin = range.valueLower;
    int valMax = range.valueUpper;

    config->SetPath("/HSV_Blue_Range_Parameter");
    config->Write("Hue_Min", hueMin);
    config->Write("Hue_Max", hueMax);
    config->Write("Saturation_Min", satMin);
    config->Write("Saturation_Max", satMax);
    config->Write("Value_Min", valMin);
    config->Write("Value_Max", valMax);
}

/**
 * @brief Reset the HSVRangeConfig of blue to default
 *
 */
void AppConfig::ResetBlueRange() {
    HSVRangeConfig r;
    r.hueLower = Default_Hue_Blue_Low;
    r.hueUpper = Default_Hue_Blue_High;
    r.saturationLower = Default_Sat_Blue_Low;
    r.saturationUpper = Default_Sat_Blue_High;
    r.valueLower = Default_Val_Blue_Low;
    r.valueUpper = Default_Val_Blue_High;

    SetBlueRange(r);
}

/**
 * @brief Get the HSVRangeConfig of yellow
 *
 * @return HSVRangeConfig
 */
HSVRangeConfig AppConfig::GetYellowRange() {
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

    HSVRangeConfig r;
    r.hueLower = hueMin;
    r.hueUpper = hueMax;
    r.saturationLower = satMin;
    r.saturationUpper = satMax;
    r.valueLower = valMin;
    r.valueUpper = valMax;
    return r;
}

/**
 * @brief Set the HSVRangeConfig of yellow
 *
 * @param range
 */
void AppConfig::SetYellowRange(HSVRangeConfig range) {
    int hueMin = range.hueLower;
    int hueMax = range.hueUpper;
    int satMin = range.saturationLower;
    int satMax = range.saturationUpper;
    int valMin = range.valueLower;
    int valMax = range.valueUpper;

    config->SetPath("/HSV_Yellow_Range_Parameter");
    config->Write("Hue_Min", hueMin);
    config->Write("Hue_Max", hueMax);
    config->Write("Saturation_Min", satMin);
    config->Write("Saturation_Max", satMax);
    config->Write("Value_Min", valMin);
    config->Write("Value_Max", valMax);
}

/**
 * @brief Reset the HSVRangeConfig of yellow to default
 *
 */
void AppConfig::ResetYellowRange() {
    HSVRangeConfig r;
    r.hueLower = Default_Hue_Yellow_Low;
    r.hueUpper = Default_Hue_Yellow_High;
    r.saturationLower = Default_Sat_Yellow_Low;
    r.saturationUpper = Default_Sat_Yellow_High;
    r.valueLower = Default_Val_Yellow_Low;
    r.valueUpper = Default_Val_Yellow_High;

    SetYellowRange(r);
}

/**
 * @brief Get the RansacConfig object
 *
 * @return RansacConfig
 */
RansacConfig AppConfig::GetRansacConfig() {
    RansacConfig ransacConfig;
    config->SetPath("/Ransac_Parameter");
    config->Read("Ransac_Threshold", &ransacConfig.threshold,
                 Default_RANSAC_Threshold);
    config->Read("Ransac_Iteration", &ransacConfig.maxIterations,
                 Default_RANSAC_Max_Iterations);
    config->Read("Ransac_Min_Points", &ransacConfig.minPoints,
                 Default_RANSAC_Min_Points);

    return ransacConfig;
}

/**
 * @brief Set the RansacConfig object
 *
 * @param ransacConfig
 */
void AppConfig::SetRansacConfig(RansacConfig ransacConfig) {
    double threshold = ransacConfig.threshold;
    int maxIterations = ransacConfig.maxIterations;
    int minPoints = ransacConfig.minPoints;

    config->SetPath("/Ransac_Parameter");
    config->Write("Ransac_Threshold", threshold);
    config->Write("Ransac_Iteration", maxIterations);
    config->Write("Ransac_Min_Points", minPoints);
}

/**
 * @brief Reset the RansacConfig object to default
 *
 */
void AppConfig::ResetRansacConfig() {
    RansacConfig ransacConfig;
    ransacConfig.threshold = Default_RANSAC_Threshold;
    ransacConfig.maxIterations = Default_RANSAC_Max_Iterations;
    ransacConfig.minPoints = Default_RANSAC_Min_Points;

    SetRansacConfig(ransacConfig);
}

/**
 * @brief Get the ThreadsConfig object
 *
 * @return ThreadsConfig
 */
ThreadsConfig AppConfig::GetThreadsConfig() {
    ThreadsConfig threadsConfig;
    config->SetPath("/Threads_Parameter");
    config->Read("Auto_Manual_Calibration",
                 &threadsConfig.autoManualCalibration,
                 Default_AutoManualCalibration);
    config->Read("Auto_Calibration", &threadsConfig.autoCalibration,
                 Default_AutoCalibration);
    config->Read("Auto_Roi", &threadsConfig.autoRoi, Default_AutoRoi);
    config->Read("Auto_Result", &threadsConfig.autoResult, Default_AutoResult);

    return threadsConfig;
}

/**
 * @brief Set the ThreadsConfig object
 *
 * @param threadsConfig
 */
void AppConfig::SetThreadsConfig(ThreadsConfig threadsConfig) {
    bool autoManualCalibration = threadsConfig.autoManualCalibration;
    bool autoCalibration = threadsConfig.autoCalibration;
    bool autoRoi = threadsConfig.autoRoi;

    config->SetPath("/Threads_Parameter");
    config->Write("Auto_Manual_Calibration", autoManualCalibration);
    config->Write("Auto_Calibration", autoCalibration);
    config->Write("Auto_Roi", autoRoi);
    config->Write("Auto_Result", threadsConfig.autoResult);
}

/**
 * @brief Reset the ThreadsConfig object to default
 *
 */
void AppConfig::ResetThreadsConfig() {
    ThreadsConfig threadsConfig;
    threadsConfig.autoManualCalibration = Default_AutoManualCalibration;
    threadsConfig.autoCalibration = Default_AutoCalibration;
    threadsConfig.autoRoi = Default_AutoRoi;
    threadsConfig.autoResult = Default_AutoResult;

    SetThreadsConfig(threadsConfig);
}

/**
 * @brief Get All Config
 *
 * @return SettingsModel All Config
 */
SettingsModel AppConfig::GetConfig() {
    SettingsModel settingsModel;
    settingsModel.modelConfig = GetModelConfig();
    settingsModel.cameraConfig = GetCameraConfig();
    settingsModel.previewConfig = GetPreviewConfig();
    settingsModel.sensorConfig = GetSensorConfig();
    settingsModel.captureConfig = GetCaptureConfig();
    settingsModel.measurementConfig = GetMeasurementConfig();
    settingsModel.opticalFlowConfig = GetOpticalFlowConfig();
    settingsModel.ransacConfig = GetRansacConfig();
    settingsModel.blueRange = GetBlueRange();
    settingsModel.yellowRange = GetYellowRange();
    settingsModel.threadsConfig = GetThreadsConfig();
    return settingsModel;
}

/**
 * @brief Reset All Config to default
 *
 */
void AppConfig::ResetConfig() {
    ResetModelConfig();
    ResetPreviewConfig();
    ResetCameraConfig();
    ResetSensorConfig();
    ResetMeasurementConfig();
    ResetCaptureConfig();
    ResetOpticalFlowConfig();
    ResetRansacConfig();
    ResetBlueRange();
    ResetYellowRange();
    ResetThreadsConfig();
}

/**
 * @brief Save All Config
 *
 * @param model
 */
void AppConfig::SaveConfig(const SettingsModel &model) {
    SetModelConfig(model.modelConfig);
    SetCameraConfig(model.cameraConfig);
    SetCaptureConfig(model.captureConfig);
    SetOpticalFlowConfig(model.opticalFlowConfig);
    SetSensorConfig(model.sensorConfig);
    SetMeasurementConfig(model.measurementConfig);
    SetPreviewConfig(model.previewConfig);
    SetRansacConfig(model.ransacConfig);
    SetBlueRange(model.blueRange);
    SetYellowRange(model.yellowRange);
    SetThreadsConfig(model.threadsConfig);
}

/**
 * @brief Destroy the App Config:: App Config object
 *
 */
AppConfig::~AppConfig() { delete config; }