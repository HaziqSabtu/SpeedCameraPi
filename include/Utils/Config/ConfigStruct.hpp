#ifndef CONFIG_STRUCT_HPP
#define CONFIG_STRUCT_HPP

#include <wx/wx.h>

#include <iostream>

struct ModelConfig {
    int Pool_Size;

    bool operator==(const ModelConfig &other) const {
        return Pool_Size == other.Pool_Size;
    }
};

struct CameraConfig {
    int Camera_ID;
    int Camera_Width;
    int Camera_Height;
    int Camera_FPS;

    bool operator==(const CameraConfig &other) const {
        return Camera_ID == other.Camera_ID &&
               Camera_Width == other.Camera_Width &&
               Camera_Height == other.Camera_Height &&
               Camera_FPS == other.Camera_FPS;
    }
};

struct CaptureConfig {
    int maxFrame;
    bool Debug;

    bool operator==(const CaptureConfig &other) const {
        return maxFrame == other.maxFrame && Debug == other.Debug;
    }
};

// Define equality operators for the remaining structs in a similar manner

struct LoadConfig {
    int maxFrame;

    bool operator==(const LoadConfig &other) const {
        return maxFrame == other.maxFrame;
    }
};

struct OpticalFlowConfig {
    int maxCorners;
    double qualityLevel;
    double minDistance;
    int blockSize;
    bool useHarrisDetector;
    double k;
    double minPointDistance;
    double threshold;

    bool operator==(const OpticalFlowConfig &other) const {
        return maxCorners == other.maxCorners &&
               qualityLevel == other.qualityLevel &&
               minDistance == other.minDistance &&
               blockSize == other.blockSize &&
               useHarrisDetector == other.useHarrisDetector && k == other.k &&
               minPointDistance == other.minPointDistance &&
               threshold == other.threshold;
    }
};

struct SensorConfig {
    double SensorWidth;
    double SensorFocalLength;

    bool operator==(const SensorConfig &other) const {
        return SensorWidth == other.SensorWidth &&
               SensorFocalLength == other.SensorFocalLength;
    }
};

struct MeasurementConfig {
    double ObjectWidth;

    bool operator==(const MeasurementConfig &other) const {
        return ObjectWidth == other.ObjectWidth;
    }
};

struct PreviewConfig {
    int width;
    int height;

    bool operator==(const PreviewConfig &other) const {
        return width == other.width && height == other.height;
    }
};

struct RansacConfig {
    double threshold;
    int minPoints;
    int maxIterations;

    bool operator==(const RansacConfig &other) const {
        return threshold == other.threshold && minPoints == other.minPoints &&
               maxIterations == other.maxIterations;
    }
};

struct HSVRangeConfig {
    int hueUpper;
    int hueLower;
    int saturationUpper;
    int saturationLower;
    int valueUpper;
    int valueLower;

    bool operator==(const HSVRangeConfig &other) const {
        return hueUpper == other.hueUpper && hueLower == other.hueLower &&
               saturationUpper == other.saturationUpper &&
               saturationLower == other.saturationLower &&
               valueUpper == other.valueUpper && valueLower == other.valueLower;
    }
};

struct SettingsModel {
    ModelConfig modelConfig;
    CameraConfig cameraConfig;
    CaptureConfig captureConfig;
    LoadConfig loadConfig;
    OpticalFlowConfig opticalFlowConfig;
    SensorConfig sensorConfig;
    MeasurementConfig measurementConfig;
    PreviewConfig previewConfig;
    RansacConfig ransacConfig;
    HSVRangeConfig blueRange;
    HSVRangeConfig yellowRange;

    bool operator==(const SettingsModel &other) const {
        return modelConfig == other.modelConfig &&
               cameraConfig == other.cameraConfig &&
               captureConfig == other.captureConfig &&
               //loadConfig == other.loadConfig &&
               opticalFlowConfig == other.opticalFlowConfig &&
               sensorConfig == other.sensorConfig &&
               measurementConfig == other.measurementConfig &&
               previewConfig == other.previewConfig &&
               ransacConfig == other.ransacConfig &&
               blueRange == other.blueRange && yellowRange == other.yellowRange;
    }

    bool operator!=(const SettingsModel &other) const {
        return !(*this == other);
    }
};

#endif