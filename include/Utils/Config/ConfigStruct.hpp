#ifndef CONFIG_STRUCT_HPP
#define CONFIG_STRUCT_HPP

struct CameraConfig {
    int Camera_ID;
    int Camera_Width;
    int Camera_Height;
    int Camera_FPS;
};

struct CaptureConfig {
    int Max_Frame_Count;
    int Frame_Interval;
    int Thread_Pool_Size;
};

#endif