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

#endif