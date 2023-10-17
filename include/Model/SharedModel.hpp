#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Process.hpp"

#include <Event/Event_ChangePanel.hpp>
#include <Event/Event_Error.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Controller.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Camera/libcam.hpp>
#include <Utils/Config/AppConfig.hpp>

#include <memory>

#include <wx/gdicmn.h>
#include <wx/wx.h>

#define ModelPtr std::shared_ptr<SharedModel>

class ISharedModel {
  public:
    virtual ~ISharedModel() = default;

    virtual void setCamera(CameraPtr &camera) = 0;
    virtual CameraPtr getCamera() = 0;
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

    void setCamera(CameraPtr &camera) override;
    CameraPtr getCamera() override;
    bool isCameraAvailable() override;

    void setThreadPool(POOLPtr threadPool) override;
    POOLPtr getThreadPool() override;

    void setThreadController(
        std::shared_ptr<ThreadController> threadController) override;

    std::shared_ptr<ThreadController> getThreadController() override;

    void killAllThreads() override;

    SessionData sessionData;
    DataPtr getSessionData();
    void setSessionData(SessionData data);
    void resetSessionData();

    void setTempSessionData(SessionData data);
    DataPtr getTempSessionData();

    bool isSessionDataChanged();

  protected:
  private:
    CameraPtr camera;
    std::shared_ptr<ThreadPool> threadPool;
    std::shared_ptr<ThreadController> threadController;

    SessionData tempSessionData;
};
