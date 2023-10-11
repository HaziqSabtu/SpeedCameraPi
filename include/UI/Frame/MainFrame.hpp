#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include "Event/Event_ChangePanel.hpp"
#include "Model/SessionData.hpp"
#include "UI/Panel/CalibrationPanel/Panel.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "UI/Panel/Common/PanelFactory.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel.hpp"
#include "UI/Panel/ResultPanel/Panel.hpp"
#include "UI/Panel/TrimDataPanel/Panel.hpp"
#include <Controller/ControllerFactory.hpp>

#include <UI/Panel/CapturePanel/Panel.hpp>
#include <UI/Panel/RoiPanel/Panel.hpp>

#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/filename.h>

class MainFrame : public wxFrame {
  public:
    MainFrame();
    ~MainFrame();

  private:
    const PanelID FIRST_PANEL_ID = PANEL_COLOR_CALIBRATION;

    std::shared_ptr<SharedModel> sharedModel;

    PanelFactoryPtr panelFactory;

    CapturePanel *cpp;
    RoiPanel *rop;
    CalibrationPanel *clp;
    ManualCalibrationPanel *mcp;
    ColorCalibrationPanel *ccp;
    TrimDataPanel *tdp;
    ResultPanel *rsp;

    std::unordered_map<PanelID, wxPanel *> panels;

    wxBoxSizer *sizer = nullptr;

    void registerPanel(PanelID panelID);

    void showFirstPanel();

    void ExitButtonHandler(wxCommandEvent &e);

    void OnError(ErrorEvent &e);
    void OnChangePanel(ChangePanelEvent &e);
    void OnButton(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};

#endif