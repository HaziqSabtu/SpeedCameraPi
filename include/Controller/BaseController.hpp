#pragma once

#include <Event/Event_UpdateState.hpp>
#include <Event/Event_UpdateStatus.hpp>

#include <Model/SessionData.hpp>
#include <Model/SharedModel.hpp>

#include <UI/Dialog/CancelDialog.hpp>

#include <Utils/CommonUtils.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Config/ConfigStruct.hpp>
#include <Utils/wxUtils.hpp>

#include <memory>
#include <vector>

#include <wx/event.h>
#include <wx/object.h>
#include <wx/thread.h>

class BaseController {
  public:
    BaseController(ModelPtr sharedModel);
    virtual ~BaseController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_PanelShow(wxEvtHandler *parent);

    void e_OKButtonHandler(wxEvtHandler *parent);
    void e_CancelButtonHandler(wxEvtHandler *parent);

    void e_CreateTempSessionData(wxEvtHandler *parent);
    void e_RestoreSessionData(wxEvtHandler *parent);
    void e_SaveSessionData(wxEvtHandler *parent);

  protected:
    ModelPtr shared;
    PanelID panelID;

  protected:
    virtual void checkPreCondition();

    virtual void throwIfAnyThreadIsRunning() = 0;

    virtual void killAllThreads(wxEvtHandler *parent) = 0;

    virtual void panelShowHandler(wxEvtHandler *parent);

    virtual void okButtonHandler(wxEvtHandler *parent);
    virtual void cancelButtonHandler(wxEvtHandler *parent);

    virtual void createTempSessionDataHandler(wxEvtHandler *parent);
    virtual void restoreSessionDataHandler(wxEvtHandler *parent);
    virtual void saveSessionDataHandler(wxEvtHandler *parent);
};

class BaseControllerWithTouch : public BaseController {
  public:
    BaseControllerWithTouch(ModelPtr shared);
    ~BaseControllerWithTouch();

    void e_LeftDown(wxEvtHandler *parent, wxPoint point);
    void e_LeftMove(wxEvtHandler *parent, wxPoint point);
    void e_LeftUp(wxEvtHandler *parent, wxPoint point);

  protected:
    virtual void leftDownHandler(wxEvtHandler *parent, cv::Point point) = 0;
    virtual void leftMoveHandler(wxEvtHandler *parent, cv::Point point) = 0;
    virtual void leftUpHandler(wxEvtHandler *parent, cv::Point point) = 0;
};