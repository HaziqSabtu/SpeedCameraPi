#pragma once

#include <Controller/BaseController.hpp>

#define DCCPtr std::shared_ptr<DistanceCalibrationController>

/**
 * @brief Controller for DistanceCalibrationPanel
 *
 */
class DistanceCalibrationController : public BaseControllerWithTouch {
  public:
    DistanceCalibrationController(ResourcePtr shared);
    ~DistanceCalibrationController();

    void e_ChangeToBottom(wxEvtHandler *parent);
    void e_ChangeToTop(wxEvtHandler *parent);

    void e_DistanceCalibrationStart(wxEvtHandler *parent);
    void e_DistanceCalibrationEnd(wxEvtHandler *parent);

    void e_DistanceCalibrationCameraStart(wxEvtHandler *parent);
    void e_DistanceCalibrationCameraEnd(wxEvtHandler *parent);

    void e_DistanceCalibrationCaptureStart(wxEvtHandler *parent);
    void e_DistanceCalibrationCaptureEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewStart(wxEvtHandler *parent);
    void e_CalibrationPreviewEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCameraStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCameraEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewCaptureStart(wxEvtHandler *parent);
    void e_CalibrationPreviewCaptureEnd(wxEvtHandler *parent);

    void e_RemoveBottom(wxEvtHandler *parent);
    void e_RemoveTop(wxEvtHandler *parent);

    void e_RemoveCalibrationData(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_DISTANCE_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void changeToBottomHandler(wxEvtHandler *parent);
    void changeToTopHandler(wxEvtHandler *parent);

    void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

    void distanceCalibrationStartHandler(wxEvtHandler *parent);
    void distanceCalibrationEndHandler(wxEvtHandler *parent);

    void distanceCalibrationCameraStartHandler(wxEvtHandler *parent);
    void distanceCalibrationCameraEndHandler(wxEvtHandler *parent);

    void distanceCalibrationCaptureStartHandler(wxEvtHandler *parent);
    void distanceCalibrationCaptureEndHandler(wxEvtHandler *parent);

    void calibrationPreviewStartHandler(wxEvtHandler *parent);
    void calibrationPreviewEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCameraStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCameraEndHandler(wxEvtHandler *parent);

    void calibrationPreviewCaptureStartHandler(wxEvtHandler *parent);
    void calibrationPreviewCaptureEndHandler(wxEvtHandler *parent);

    void removeBottomHandler(wxEvtHandler *parent);
    void removeTopHandler(wxEvtHandler *parent);

    void removeCalibrationDataHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};