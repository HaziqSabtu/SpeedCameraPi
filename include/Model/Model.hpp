#pragma once

#include <Model/ModelEnum.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Capture.hpp>
#include <Thread/Thread_LoadFile.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Camera/libcam.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>

#include <wx/wx.h>

class Model : public wxPanel {
  public:
    Model(wxWindow* parent, wxWindowID id);
    ~Model();
    void endPoint(wxEvtHandler* parent, ModelEnum::ModelIDs id);
    void endPoint(wxEvtHandler* parent,
                  ModelEnum::ModelIDs id,
                  std::string path);

  private:
    LibCam camera;

    std::shared_ptr<ThreadPool> threadPool;
    std::shared_ptr<std::vector<ImageData>> imgData;

    CaptureThread* captureThread;
    LoadFileThread* loadFileThread;

    void init();

    void startCaptureHandler(wxEvtHandler* parent);
    void endCaptureHandler(wxEvtHandler* parent);

    void LoadFileHandler(wxEvtHandler* parent, std::string path);

    template <typename T>
    T* stopAndDeleteThread(T* threadPtr);
};