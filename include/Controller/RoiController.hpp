#pragma once

#include <Controller/BaseController.hpp>

#define ROCPtr std::shared_ptr<RoiController>

class RoiController : public BaseControllerWithTouch {
  public:
    RoiController(ModelPtr sharedModel);
    ~RoiController();

    void e_ClearRect(wxEvtHandler *parent);
    void e_RemoveRect(wxEvtHandler *parent);

    // void e_SetPoint1(wxEvtHandler *parent, wxPoint point);
    // void e_SetPoint2(wxEvtHandler *parent, wxPoint point);
    // void e_SaveRect(wxEvtHandler *parent, wxPoint point);

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

    void leftDownHandler(wxEvtHandler *parent, cv::Point point);
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point);
    void leftUpHandler(wxEvtHandler *parent, cv::Point point);
    // void setPoint1Handler(wxEvtHandler *parent, cv::Point point);
    // void setPoint2Handler(wxEvtHandler *parent, cv::Point point);
    // void saveRectHandler(wxEvtHandler *parent, cv::Point point);

    void roiThreadStartHandler(wxEvtHandler *parent);
    void roiThreadSaveHandler(wxEvtHandler *parent);
    void roiThreadCancelHandler(wxEvtHandler *parent);

    void roiPreviewStartHandler(wxEvtHandler *parent);
    void roiPreviewEndHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};