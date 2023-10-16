#pragma once

#include "Controller/BaseController.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/AppState.hpp"
#include "Model/SessionData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/Panel_Image.hpp"
#include <wx/wx.h>

class BaseButtonPanel : public wxPanel {
  public:
    BaseButtonPanel(wxWindow *parent, wxWindowID id)
        : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {}
    ~BaseButtonPanel() {}

    virtual void update(const AppState &state) = 0;

  protected:
    wxBoxSizer *main_sizer;
};

#define BSCPtr std::shared_ptr<BaseController>
#define BTCPtr std::shared_ptr<BaseControllerWithTouch>

class BasePanel : public wxPanel {
  public:
    BasePanel(wxWindow *parent, wxWindowID id, BSCPtr controller);
    ~BasePanel();

  protected:
    TitlePanel *title_panel;
    BaseImagePanel *img_bitmap;
    StatusPanel *status_panel;
    BaseButtonPanel *button_panel;

    wxBoxSizer *main_sizer;

    BSCPtr controller;

    void size();

    void OnButton(wxCommandEvent &e);
    void OnShow(wxShowEvent &e);
    void OnRequestUpdateState(wxCommandEvent &e);
    void OnUpdatePreview(UpdatePreviewEvent &e);
    void OnUpdateStatus(UpdateStatusEvent &e);
    void OnUpdateState(UpdateStateEvent &e);

    DECLARE_EVENT_TABLE()
};

class BasePanelWithTouch : public BasePanel {
  public:
    BasePanelWithTouch(wxWindow *parent, wxWindowID id, BTCPtr controller);
    ~BasePanelWithTouch();

  protected:
    BTCPtr controller;

    void bindLeftDown();
    void bindMotion();
    void bindLeftUp();
    void bindAll();

    void unBindLeftDown();
    void unBindMotion();
    void unBindLeftUp();
    void unBindAll();

    void OnLeftDown(wxMouseEvent &e);
    void OnMotion(wxMouseEvent &e);
    void OnLeftUp(wxMouseEvent &e);

    virtual void doPostLeftDown();
    virtual void doPostMotion();
    virtual void doPostLeftUp();

    DECLARE_EVENT_TABLE()
};
