#pragma once

#include "UI/StaticText/Statustext.hpp"
#include "UI/Theme/Theme.hpp"
#include <wx/gtk/stattext.h>
#include <wx/string.h>
#include <wx/wx.h>

namespace StatusCollection {
const wxString STATUS_IDLE = wxT("Idle");

// TODO : CLeanup
// clang-format off
// Statuses for CalibrationPanel
const wxString STATUS_START_CALIBRATION = wxT("Start Calibration");
const wxString STATUS_CALIBRATION_SUCCESS = wxT("Calibration Success");
const wxString STATUS_CALIBRATION_END = wxT("Calibration End");
const wxString STATUS_CALIBRATION_FAIL = wxT("Calibration Fail");
const wxString STATUS_LINE_DETECTED = wxT("Line Detected");
const wxString STATUS_LINE_NOT_DETECTED = wxT("Error Detecting Line");
const wxString STATUS_CAMERA_ON = wxT("Camera On");
const wxString STATUS_CAMERA_OFF = wxT("Camera Off");

const wxString STATUS_CAPTURE_START = wxT("Capture Start");
const wxString STATUS_CAPTURE_END = wxT("Capture Success");
const wxString STATUS_CAPTURE_ERROR = wxT("Capture Error");

const wxString STATUS_LOAD_DATA_START = wxT("Loading Data");
const wxString STATUS_LOAD_DATA_END = wxT("Data Loaded");
const wxString STATUS_LOAD_DATA_ERROR = wxT("Error Loading Data");
const wxString STATUS_LOAD_DATA_CANCEL = wxT("Data Load Cancelled");

const wxString STATUS_REMOVE_DATA = wxT("Data Removed");
const wxString STATUS_PREVIEW_CAPTURE_START = wxT("Preview Start [CAPTURE]");
const wxString STATUS_PREVIEW_CAPTURE_END = wxT("Preview End [CAPTURE]");
const wxString STATUS_PREVIEW_CAPTURE_ERROR = wxT("Preview Error [CAPTURE]");
const wxString STATUS_PREVIEW_CAMERA_START = wxT("Preview Start [CAMERA]");
const wxString STATUS_PREVIEW_CAMERA_END = wxT("Preview End [CAMERA]");
const wxString STATUS_PREVIEW_CAMERA_ERROR = wxT("Preview Error [CAMERA]");

} // namespace StatusCollection
// clang-format on

namespace SC = StatusCollection;

class StatusPanel : public wxPanel {
  public:
    StatusPanel(wxWindow *parent, wxString stat = SC::STATUS_IDLE);
    ~StatusPanel();

    void SetText(wxString text);

  private:
    StatusText *statusText;

    wxStaticText *emptySpacerLeft;
    wxStaticText *emptySpacerRight;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;
};