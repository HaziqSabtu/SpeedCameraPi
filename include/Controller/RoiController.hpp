#pragma once

#include <Controller/BaseController.hpp>

#define ROCPtr std::shared_ptr<RoiController>

/**
 * @brief Controller for RoiPanel
 *
 */
class RoiController : public BaseControllerWithTouch {
  public:
    RoiController(ResourcePtr shared);
    ~RoiController();

    void e_ClearRect(wxEvtHandler *parent);
    void e_RemoveRect(wxEvtHandler *parent);

    void e_RoiThreadStart(wxEvtHandler *parent);
    void e_RoiThreadSave(wxEvtHandler *parent);
    void e_RoiThreadCancel(wxEvtHandler *parent);

    void e_RoiPreviewStart(wxEvtHandler *parent);
    void e_RoiPreviewEnd(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_ROI;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void clearRectHandler(wxEvtHandler *parent);
    void removeRectHandler(wxEvtHandler *parent);

    void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

    void roiThreadStartHandler(wxEvtHandler *parent);
    void roiThreadSaveHandler(wxEvtHandler *parent);
    void roiThreadCancelHandler(wxEvtHandler *parent);

    void roiPreviewStartHandler(wxEvtHandler *parent);
    void roiPreviewEndHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};