#pragma once

#include <Controller/BaseController.hpp>

#define LMCPtr std::shared_ptr<LaneManualCalibrationController>

class LaneManualCalibrationController : public BaseControllerWithTouch {
  public:
    LaneManualCalibrationController(ModelPtr sharedModel);
    ~LaneManualCalibrationController();

    void e_ChangeToLeft(wxEvtHandler *parent);
    void e_ChangeToRight(wxEvtHandler *parent);

    void e_ManualCalibrationStart(wxEvtHandler *parent);
    void e_ManualCalibrationEnd(wxEvtHandler *parent);

    void e_ManualCalibrationCameraStart(wxEvtHandler *parent);
    void e_ManualCalibrationCameraEnd(wxEvtHandler *parent);

    void e_ManualCalibrationCaptureStart(wxEvtHandler *parent);
    void e_ManualCalibrationCaptureEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewStart(wxEvtHandler *parent);
    void e_CalibrationPreviewEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCameraStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCameraEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCaptureStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCaptureEnd(wxEvtHandler *parent);

    void e_RemoveLeft(wxEvtHandler *parent);
    void e_RemoveRight(wxEvtHandler *parent);

    void e_RemoveCalibrationData(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID =
        PanelID::PANEL_LANE_MANUAL_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void changeToLeftHandler(wxEvtHandler *parent);
    void changeToRightHandler(wxEvtHandler *parent);

    void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

    void manualCalibrationStartHandler(wxEvtHandler *parent);
    void manualCalibrationEndHandler(wxEvtHandler *parent);

    void manualCalibrationCameraStartHandler(wxEvtHandler *parent);
    void manualCalibrationCameraEndHandler(wxEvtHandler *parent);

    void manualCalibrationCaptureStartHandler(wxEvtHandler *parent);
    void manualCalibrationCaptureEndHandler(wxEvtHandler *parent);

    void calibrationPreviewStartHandler(wxEvtHandler *parent);
    void calibrationPreviewEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCameraStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCameraEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCaptureStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCaptureEndHandler(wxEvtHandler *parent);

    void removeLeftHandler(wxEvtHandler *parent);
    void removeRightHandler(wxEvtHandler *parent);

    void removeCalibrationDataHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};