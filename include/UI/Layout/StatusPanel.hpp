#pragma once

#include "UI/StaticText/Statustext.hpp"
#include <wx/gtk/stattext.h>
#include <wx/string.h>
#include <wx/wx.h>

namespace StatusCollection {
const wxString STATUS_IDLE = wxT("Idle");

// Statuses for CalibrationPanel
const wxString STATUS_START_CALIBRATION = wxT("Start Calibration");
const wxString STATUS_CALIBRATION_SUCCESS = wxT("Calibration Success");
const wxString STATUS_CALIBRATION_FAIL = wxT("Calibration Fail");
const wxString STATUS_LINE_DETECTED = wxT("Line Detected");
const wxString STATUS_LINE_NOT_DETECTED = wxT("Error Detecting Line");
const wxString STATUS_CAMERA_ON = wxT("Camera On");
const wxString STATUS_CAMERA_OFF = wxT("Camera Off");

} // namespace StatusCollection

class StatusPanel : public wxPanel {
  public:
    StatusPanel(wxWindow *parent, wxString stat);
    ~StatusPanel();

    void SetText(wxString text);

  private:
    StatusText *statusText;

    wxStaticText *emptySpacerLeft;
    wxStaticText *emptySpacerRight;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};