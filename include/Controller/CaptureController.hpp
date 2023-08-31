#pragma once

#include <Controller/BaseController.hpp>

#include <Event/Event_ChangePanel.hpp>
#include <Event/Event_UpdatePreview.hpp>
#include <Event/Event_UpdateState.hpp>
#include <Event/Event_UpdateStatus.hpp>

#include <Model/AppState.hpp>
#include <Model/SessionData.hpp>
#include <Model/SharedModel.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Controller.hpp>

#include <UI/Dialog/ResetDataDialog.hpp>
#include <UI/Dialog/SaveDataDialog.hpp>
#include <UI/Layout/StatusPanel.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Config/ConfigStruct.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <Utils/wxUtils.hpp>

#include <memory>
#include <vector>

#include <wx/event.h>
#include <wx/thread.h>

#define CPCPtr std::shared_ptr<CaptureController>

class CaptureController : public BaseController {
  public:
    CaptureController(ModelPtr sharedModel);
    ~CaptureController();

    void e_ClearImageData(wxEvtHandler *parent);

    void e_CameraPreviewStart(wxEvtHandler *parent);
    void e_CameraPreviewEnd(wxEvtHandler *parent);

    void e_LoadFileStart(wxEvtHandler *parent, std::string path);
    void e_LoadFileEnd(wxEvtHandler *parent);

    void e_LoadCaptureStart(wxEvtHandler *parent);
    void e_LoadCaptureEnd(wxEvtHandler *parent);

    void e_CapturePreviewStart(wxEvtHandler *parent);
    void e_CapturePreviewEnd(wxEvtHandler *parent);

    void e_ChangeToCalibrationPanel(wxEvtHandler *parent);
    void e_RemoveCalibration(wxEvtHandler *parent);

    void e_ChangeToRoiPanel(wxEvtHandler *parent);
    void e_RemoveRoi(wxEvtHandler *parent);

    void e_ChangeToResultPanel(wxEvtHandler *parent);

    void e_SaveSessionDataStart(wxEvtHandler *parent);
    void e_SaveSessionDataEnd(wxEvtHandler *parent);
    void e_ResetSessionData(wxEvtHandler *parent);

    void e_ChangeToTrimDataPanel(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_CAPTURE;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void clearImageDataHandler(wxEvtHandler *parent);

    void removeCalibrationHandler(wxEvtHandler *parent);

    void removeRoiHandler(wxEvtHandler *parent);

    void cameraPreviewStartHandler(wxEvtHandler *parent);
    void cameraPreviewEndHandler(wxEvtHandler *parent);

    void loadFileStartHandler(wxEvtHandler *parent, std::string path);
    void loadFileEndHandler(wxEvtHandler *parent);

    void loadCaptureStartHandler(wxEvtHandler *parent);
    void loadCaptureEndHandler(wxEvtHandler *parent);

    void capturePreviewStartHandler(wxEvtHandler *parent);
    void capturePreviewEndHandler(wxEvtHandler *parent);

    void saveSessionDataStartHandler(wxEvtHandler *parent);
    void saveSessionDataEndHandler(wxEvtHandler *parent);

    void resetSessionDataHandler(wxEvtHandler *parent);

    void changeToCalibPanelHandler(wxEvtHandler *parent);
    void changeToRoiPanelHandler(wxEvtHandler *parent);
    void changeToResultPanelHandler(wxEvtHandler *parent);

    void changeToTrimDataPanelHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
    void okButtonHandler(wxEvtHandler *parent) override;
    void cancelButtonHandler(wxEvtHandler *parent) override;
};