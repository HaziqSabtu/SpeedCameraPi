#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include "Event/Event_ChangePanel.hpp"
#include "Model/SessionData.hpp"
#include "UI/Panel/CalibrationPanel/Panel.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel.hpp"
#include <Model/ModelFactory.hpp>

#include <UI/Panel/CapturePanel/Panel.hpp>
#include <UI/Panel/RoiPanel/Panel.hpp>

#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/filename.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title);
    ~MainFrame();

  private:
    std::shared_ptr<SharedModel> sharedModel;

    CapturePanel *capture_panel;
    RoiPanel *roi_panel;
    CalibrationPanel *calibration_panel;
    ManualCalibrationPanel *manual_calibration_panel;
    ColorCalibrationPanel *color_calibration_panel;

    // TODO: Is there a better way to do this?
    std::unordered_map<PanelID, wxPanel *> panels;

    wxBoxSizer *sizer;

    void OnError(ErrorEvent &e);
    void OnChangePanel(ChangePanelEvent &e);
    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};

#endif