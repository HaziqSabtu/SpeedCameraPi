#pragma once

#include <Algorithm/Struct/D_Line.hpp>

#include <Controller/BaseController.hpp>

#include <Event/Event_UpdateState.hpp>

#include <Model/AppState.hpp>
#include <Model/CalibrationData.hpp>
#include <Model/SessionData.hpp>
#include <Model/SharedModel.hpp>

#include <Thread/Thread_Controller.hpp>

#include <UI/Dialog/CancelDialog.hpp>

#include <Utils/wxUtils.hpp>

#include <wx/event.h>

#define HCCPtr std::shared_ptr<HorizontalCalibrationController>

class HorizontalCalibrationController : public BaseControllerWithTouch {
  public:
    HorizontalCalibrationController(ModelPtr sharedModel);
    ~HorizontalCalibrationController();

    void e_ChangeToBottom(wxEvtHandler *parent);
    void e_ChangeToTop(wxEvtHandler *parent);

    void e_HorizontalCalibrationCameraStart(wxEvtHandler *parent);
    void e_HorizontalCalibrationCameraEnd(wxEvtHandler *parent);

    void e_HorizontalCalibrationCaptureStart(wxEvtHandler *parent);
    void e_HorizontalCalibrationCaptureEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCameraStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCameraEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCaptureStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCaptureEnd(wxEvtHandler *parent);

    void e_RemoveBottom(wxEvtHandler *parent);
    void e_RemoveTop(wxEvtHandler *parent);

    void e_RemoveCalibrationData(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_HORIZONTAL_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void changeToBottomHandler(wxEvtHandler *parent);
    void changeToTopHandler(wxEvtHandler *parent);

    void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

    void horizontalCalibrationCameraStartHandler(wxEvtHandler *parent);
    void horizontalCalibrationCameraEndHandler(wxEvtHandler *parent);

    void horizontalCalibrationCaptureStartHandler(wxEvtHandler *parent);
    void horizontalCalibrationCaptureEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCameraStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCameraEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCaptureStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCaptureEndHandler(wxEvtHandler *parent);

    void removeBottomHandler(wxEvtHandler *parent);
    void removeTopHandler(wxEvtHandler *parent);

    void removeCalibrationDataHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};