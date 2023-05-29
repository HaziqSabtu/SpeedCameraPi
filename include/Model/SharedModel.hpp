#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Process.hpp"
#include <Model/ModelEnum.hpp>

#include <Event/Event_ChangePanel.hpp>
#include <Event/Event_Error.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Capture.hpp>
#include <Thread/Thread_LoadCapture.hpp>
#include <Thread/Thread_LoadFile.hpp>
#include <Thread/Thread_Process.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Camera/libcam.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>

#include <wx/gdicmn.h>
#include <wx/wx.h>

class SharedModel {
  public:
    SharedModel(wxWindow *parent);
    ~SharedModel();

    SessionData sessionData;
    std::shared_ptr<CameraBase> camera;
    std::shared_ptr<ThreadPool> threadPool;
};