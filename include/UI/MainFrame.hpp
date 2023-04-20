#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <Model/Model.hpp>

#include <UI/Panel/CapturePanel/Panel.hpp>
#include <UI/Panel/RoiPanel/Panel.hpp>

#include <Utils/Enum.hpp>

#include <wx/filename.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title, wxSize size, AppConfig *config);
    ~MainFrame();

  private:
    CapturePanel *capture_panel;
    RoiPanel *roi_panel;

    Model *model;
    wxBoxSizer *sizer;

    void OnPageChange(wxCommandEvent &e);
    void OnError(ErrorEvent &e);

    DECLARE_EVENT_TABLE()
};

#endif