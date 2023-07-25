#pragma once

#include "Model/AppState.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Controller.hpp"
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

class ISharedModel {
  public:
    virtual ~ISharedModel() = default;

    virtual void setCamera(std::unique_ptr<CameraBase> &camera) = 0;
    virtual std::unique_ptr<CameraBase> getCamera() = 0;
    virtual bool isCameraAvailable() = 0;

    virtual void setThreadPool(std::shared_ptr<ThreadPool> threadPool) = 0;
    virtual std::shared_ptr<ThreadPool> getThreadPool() = 0;

    virtual void
    setThreadController(std::shared_ptr<ThreadController> threadController) = 0;
    virtual std::shared_ptr<ThreadController> getThreadController() = 0;
    virtual void killAllThreads() = 0;
};

class SharedModel : public ISharedModel {
  public:
    SharedModel();
    ~SharedModel();

    void setCamera(std::unique_ptr<CameraBase> &camera) override;
    std::unique_ptr<CameraBase> getCamera() override;
    bool isCameraAvailable() override;

    void setThreadPool(std::shared_ptr<ThreadPool> threadPool) override;
    std::shared_ptr<ThreadPool> getThreadPool() override;

    void setThreadController(
        std::shared_ptr<ThreadController> threadController) override;

    std::shared_ptr<ThreadController> getThreadController() override;

    void killAllThreads() override;

    AppState getAppState();
    SessionData sessionData;

  protected:
    CameraPanelState getCameraPanelState();

  private:
    std::unique_ptr<CameraBase> camera;
    std::shared_ptr<ThreadPool> threadPool;
    std::shared_ptr<ThreadController> threadController;

    ButtonState getCaptureButtonState();
    ButtonState getLoadButtonState();
    ButtonState getReplayButtonState();
    ButtonState getRemoveButtonState();
};