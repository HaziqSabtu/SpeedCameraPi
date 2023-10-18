#pragma once

#include <Controller/BaseController.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>
#include <Utils/Camera/CameraBase.hpp>

#define LCCPtr std::shared_ptr<LaneCalibrationController>

class LaneCalibrationController : public BaseControllerWithTouch {
  public:
    LaneCalibrationController(ResourcePtr shared);
    ~LaneCalibrationController();

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
    static const PanelID currentPanelID = PanelID::PANEL_LANE_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void saveCalibrationData(wxEvtHandler *parent,
                             BaseLaneCalibrationThread *thread);

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