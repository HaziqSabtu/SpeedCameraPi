#pragma once

#include <Controller/BaseController.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <Utils/wxUtils.hpp>

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

    void e_ChangeToLaneCalibrationPanel(wxEvtHandler *parent);
    void e_RemoveCalibration(wxEvtHandler *parent);

    void e_ChangeToDistanceCalibrationPanel(wxEvtHandler *parent);

    void e_ChangeToRoiPanel(wxEvtHandler *parent);
    void e_RemoveRoi(wxEvtHandler *parent);

    void e_ChangeToResultPanel(wxEvtHandler *parent);

    void e_SaveSessionDataStart(wxEvtHandler *parent);
    void e_SaveSessionDataEnd(wxEvtHandler *parent);
    void e_ResetSessionData(wxEvtHandler *parent);

    void e_ChangeToTrimDataPanel(wxEvtHandler *parent);

    void e_ToggleMode(wxEvtHandler *parent);

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

    void changeToLaneCalibrationPanelHandler(wxEvtHandler *parent);
    void changeToRoiPanelHandler(wxEvtHandler *parent);
    void changeToResultPanelHandler(wxEvtHandler *parent);

    void changeToTrimDataPanelHandler(wxEvtHandler *parent);

    void changeToDistanceCalibrationPanelHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
    void okButtonHandler(wxEvtHandler *parent) override;
    void cancelButtonHandler(wxEvtHandler *parent) override;

    void toggleModeHandler(wxEvtHandler *parent);
};