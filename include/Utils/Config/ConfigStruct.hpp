#ifndef CONFIG_STRUCT_HPP
#define CONFIG_STRUCT_HPP

#include <wx/wx.h>

struct ModelConfig {
    int Pool_Size;
};
struct CameraConfig {
    int Camera_ID;
    int Camera_Width;
    int Camera_Height;
    int Camera_FPS;
};

struct CaptureConfig {
    int maxFrame;
    bool Debug;
};

struct LoadConfig {
    int maxFrame;
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
};

struct SensorConfig {
    double SensorWidth;
    double SensorFocalLength;
    double ObjectWidth;
};

struct PreviewConfig {
    int width;
    int height;
};

struct RansacConfig {
    double threshold;
    int minPoints;
    int maxIterations;
};

#endif