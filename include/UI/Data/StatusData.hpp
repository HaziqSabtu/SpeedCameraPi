#pragma once

#include <wx/wx.h>

namespace StatusCollection {
const wxString STATUS_IDLE = wxT("Idle");

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


const wxString STATUS_REMOVE_CALIBRATION_OK = wxT("Calibration Removed");
const wxString STATUS_REMOVE_ROI_OK = wxT("ROI Removed");


const wxString STATUS_SAVE_DATA_START = wxT("Saving Data");
const wxString STATUS_SAVE_DATA_END = wxT("Data Saved");
const wxString STATUS_SAVE_DATA_ERROR = wxT("Error Saving Data");
const wxString STATUS_SAVE_DATA_CANCEL = wxT("Data Save Cancelled");

const wxString STATUS_RESET_SESSION_CANCEL = wxT("Reset Session Cancelled");
const wxString STATUS_RESET_SESSION_OK = wxT("Session Reset");

const wxString STATUS_CALIBRATION_CAMERA_START = wxT("Calibration Start [CAMERA]");
const wxString STATUS_CALIBRATION_CAMERA_END = wxT("Calibration End [CAMERA]");
const wxString STATUS_CALIBRATION_CAMERA_ERROR = wxT("Calibration Error [CAMERA]");

const wxString STATUS_CALIBRATION_CAPTURE_START = wxT("Calibration Start [CAPTURE]");
const wxString STATUS_CALIBRATION_CAPTURE_END = wxT("Calibration End [CAPTURE]");
const wxString STATUS_CALIBRATION_CAPTURE_ERROR = wxT("Calibration Error [CAPTURE]");

const wxString STATUS_CALIBRATION_NOPOINT = wxT("No Point Selected");
const wxString STATUS_CALIBRATION_SELECTPOINT = wxT("Select Point");
const wxString STATUS_CALIBRATION_POINTSELECTED = wxT("Point Selected");
const wxString STATUS_CALIBRATION_POINTREMOVED = wxT("Point Removed");
const wxString STATUS_CALIBRATION_LINENOTFOUND = wxT("Line Not Found");
const wxString STATUS_CALIBRATION_LINEOK = wxT("Line Found");

const wxString STATUS_MANUAL_SELECTLEFT = wxT("Select Left Line");
const wxString STATUS_MANUAL_REMOVELEFT = wxT("Left Line Removed");
const wxString STATUS_MANUAL_SELECTRIGHT = wxT("Select Right Line");
const wxString STATUS_MANUAL_REMOVERIGHT = wxT("Right Line Removed");

const wxString STATUS_HORIZONTAL_SELECTTOP = wxT("Select Top Line");
const wxString STATUS_HORIZONTAL_REMOVETOP = wxT("Top Line Removed");
const wxString STATUS_HORIZONTAL_SELECTBOTTOM = wxT("Select Bottom Line");
const wxString STATUS_HORIZONTAL_REMOVEBOTTOM = wxT("Bottom Line Removed");

const wxString STATUS_ROI_SELECT = wxT("Select ROI");
const wxString STATUS_ROI_SELECTED = wxT("ROI Selected");
const wxString STATUS_ROI_REMOVE = wxT("Roi Removed");
const wxString STATUS_ROI_ERROR = wxT("Error Selecting ROI");
const wxString STATUS_ROI_SAVE = wxT("ROI Saved");

const wxString STATUS_PROCESSING_START = wxT("Processing");
const wxString STATUS_PROCESSING_END = wxT("Processing End");
const wxString STATUS_PROCESSING_ERROR = wxT("Processing Error");


const wxString STATUS_RESULT_PREVIEW_START = wxT("Preview Start");
const wxString STATUS_RESULT_PREVIEW_END = wxT("Preview End");
const wxString STATUS_RESULT_PREVIEW_ERROR = wxT("Preview Error");

const wxString STATUS_RESULT_PREVIEW_SHOWBOX_ON = wxT("Show Box On");
const wxString STATUS_RESULT_PREVIEW_SHOWBOX_OFF = wxT("Show Box Off");

const wxString STATUS_RESULT_PREVIEW_SHOWLINES_ON = wxT("Show Lines On");
const wxString STATUS_RESULT_PREVIEW_SHOWLINES_OFF = wxT("Show Lines Off");

const wxString STATUS_RESULT_PREVIEW_SHOWLANES_ON = wxT("Show Lanes On");
const wxString STATUS_RESULT_PREVIEW_SHOWLANES_OFF = wxT("Show Lanes Off");

const wxString STATUS_RESULT_PREVIEW_REPLAY = wxT("Replay");

const wxString STATUS_SWITCH_MODE_CANCEL = wxT("Switch Mode Cancelled");
const wxString STATUS_SWITCH_MODE_OK = wxT("Mode Switched");
const wxString STATUS_SWITCH_MODE_ERROR = wxT("Error Switching Mode");

} // namespace StatusCollection
// clang-format on