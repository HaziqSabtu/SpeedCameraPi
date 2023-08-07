#ifndef CONFIG_STRUCT_HPP
#define CONFIG_STRUCT_HPP

#include <wx/wx.h>

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
    wxString path;
    int maxFrame;
};

struct PanelConfig {
    int Thread_Pool_Size;
};

struct CannyConfig {
    double threshold1;
    double threshold2;
    int apertureSize;
    bool L2gradient;
};

struct HoughConfig {
    double rho;
    double theta;
    int threshold;
    double minLineLength;
    double maxLineGap;
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