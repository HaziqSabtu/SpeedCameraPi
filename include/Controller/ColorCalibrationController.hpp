#pragma once

#include <Controller/BaseController.hpp>

#define CCCPtr std::shared_ptr<ColorCalibrationController>

class ColorCalibrationController : public BaseControllerWithTouch {
  public:
    ColorCalibrationController(ModelPtr sharedModel);
    ~ColorCalibrationController();

    void e_SaveToConfig(wxEvtHandler *parent);

    void e_RestoreRange(wxEvtHandler *parent);

    void e_RemoveCalibratedRange(wxEvtHandler *parent);

    void e_SetTypeBlue(wxEvtHandler *parent);
    void e_SetTypeYellow(wxEvtHandler *parent);

    void e_ColorCalibrationStart(wxEvtHandler *parent);
    void e_ColorCalibrationEnd(wxEvtHandler *parent);

    void e_ColorCalibrationPreviewStart(wxEvtHandler *parent);
    void e_ColorCalibrationPreviewEnd(wxEvtHandler *parent);

    void e_RemoveBlue(wxEvtHandler *parent);
    void e_RemoveYellow(wxEvtHandler *parent);

    void e_SaveBlue(wxEvtHandler *parent);
    void e_SaveYellow(wxEvtHandler *parent);

    void e_SaveColorCalibration(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_COLOR_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

    void saveToConfigHandler(wxEvtHandler *parent);

    void restoreRangeHandler(wxEvtHandler *parent);

    void removeCalibratedRangeHandler(wxEvtHandler *parent);

    void setTypeBlueHandler(wxEvtHandler *parent);
    void setTypeYellowHandler(wxEvtHandler *parent);

    void colorCalibrationStartHandler(wxEvtHandler *parent);
    void colorCalibrationEndHandler(wxEvtHandler *parent);

    void colorCalibrationPreviewStartHandler(wxEvtHandler *parent);
    void colorCalibrationPreviewEndHandler(wxEvtHandler *parent);

    void removeBlueHandler(wxEvtHandler *parent);
    void removeYellowHandler(wxEvtHandler *parent);

    void saveBlueHandler(wxEvtHandler *parent);
    void saveYellowHandler(wxEvtHandler *parent);

    void saveColorCalibrationHandler(wxEvtHandler *parent);
};