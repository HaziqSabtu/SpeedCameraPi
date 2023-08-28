#pragma once

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
    BaseButtonPanel(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {}
    ~BaseButtonPanel() {}

    virtual void update(const AppState &state) = 0;

  protected:
    wxBoxSizer *main_sizer;
};

class BasePanel : public wxPanel {
  public:
    BasePanel(wxWindow *parent, wxWindowID id);
    ~BasePanel();

  protected:
    TitlePanel *title_panel;
    BaseImagePanel *img_bitmap;
    StatusPanel *status_panel;
    BaseButtonPanel *button_panel;

    wxBoxSizer *main_sizer;

    PanelID panel_id;

    void size();

    virtual void OnUpdatePreview(UpdatePreviewEvent &e);
    virtual void OnShow(wxShowEvent &e);
    virtual void OnUpdateStatus(UpdateStatusEvent &e);
    virtual void OnUpdateState(UpdateStateEvent &e);

    DECLARE_EVENT_TABLE()
};