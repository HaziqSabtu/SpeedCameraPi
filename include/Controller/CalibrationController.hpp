#pragma once

#include <Algorithm/hsv_filter/BFS.hpp>
#include <Algorithm/hsv_filter/HSVFilter.hpp>
#include <Algorithm/ransac_line/RansacLine.hpp>

#include <Controller/BaseController.hpp>

#include <Event/Event_UpdateState.hpp>

#include <Model/SessionData.hpp>
#include <Model/SharedModel.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Controller.hpp>

#include <UI/Dialog/CancelDialog.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Config/ConfigStruct.hpp>

#include <memory>
#include <vector>

#include <wx/event.h>
#include <wx/object.h>
#include <wx/thread.h>

#define CLCPtr std::shared_ptr<CalibrationController>

class CalibrationController : public BaseControllerWithTouch {
  public:
    CalibrationController(ModelPtr sharedModel);
    ~CalibrationController();

    void e_RemoveCalibrationData(wxEvtHandler *parent);

    void e_ClearPoint(wxEvtHandler *parent);

    void e_SaveData(wxEvtHandler *parent);

    void e_CalibrationStart(wxEvtHandler *parent);
    void e_CalibrationEnd(wxEvtHandler *parent);

    void e_CalibrationCameraStart(wxEvtHandler *parent);
    void e_CalibrationCameraEnd(wxEvtHandler *parent);

    void e_CalibrationCaptureStart(wxEvtHandler *parent);
    void e_CalibrationCaptureEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewStart(wxEvtHandler *parent);
    void e_CalibrationPreviewEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCameraStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCameraEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCaptureStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCaptureEnd(wxEvtHandler *parent);

    void e_ChangeToManualPanel(wxEvtHandler *parent);
    void e_ChangeToColorPanel(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void saveCalibrationData(wxEvtHandler *parent,
                             BaseCalibrationThread *thread);

    void saveDataHandler(wxEvtHandler *parent);

    void calibrationStartHandler(wxEvtHandler *parent);
    void calibrationEndHandler(wxEvtHandler *parent);

    void calibrationCameraStartHandler(wxEvtHandler *parent);
    void calibrationCameraEndHandler(wxEvtHandler *parent);

    void calibrationCaptureStartHandler(wxEvtHandler *parent);
    void calibrationCaptureEndHandler(wxEvtHandler *parent);

    void calibrationPreviewStartHandler(wxEvtHandler *parent);
    void calibrationPreviewEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCameraStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCameraEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCaptureStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCaptureEndHandler(wxEvtHandler *parent);

    void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

    void clearPointHandler(wxEvtHandler *parent);

    void removeCalibrationDataHandler(wxEvtHandler *parent);

    void changeToManualPanelHandler(wxEvtHandler *parent);
    void changeToColorPanelHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};