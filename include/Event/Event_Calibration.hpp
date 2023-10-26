/**
 * @file Event_Calibration.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Calibration Process
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_CALIBRATION_EVENT, wxCommandEvent);

/**
 * @brief Enum for Calibration Process
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_CAMERA_START</td>
 *   <td>Event for Signaling Starting of Calibration process with Camera</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_CAMERA_END</td>
 *   <td>Event for Signaling Ending of Calibration process with Camera</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_CAMERA_ERROR</td>
 *   <td>Event for Signaling Error of Calibration process with Camera</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_CAPTURE_START</td>
 *   <td>Event for Signaling Starting of Calibration process with Image</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_CAPTURE_END</td>
 *   <td>Event for Signaling Ending of Calibration process with Image</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_CAPTURE_ERROR</td>
 *   <td>Event for Signaling Error of Calibration process with Image</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_LINE_FOUND</td>
 *   <td>Event for Signaling Line Found during Calibration process, this Event
 * is used within LaneCalibrationThread</td>
 * </tr>
 * <tr>
 *   <td>CALIBRATION_LINE_NOT_FOUND</td>
 *   <td>Event for Signaling Line Not Found during Calibration process, this
 * Event is used within LaneCalibrationThread</td>
 * </tr>
 *
 */
enum CALIBRATION_EVENT_TYPE {
    CALIBRATION_CAMERA_START = 1,
    CALIBRATION_CAMERA_END,
    CALIBRATION_CAMERA_ERROR,

    CALIBRATION_CAPTURE_START,
    CALIBRATION_CAPTURE_END,
    CALIBRATION_CAPTURE_ERROR,

    CALIBRATION_LINE_FOUND,
    CALIBRATION_LINE_NOT_FOUND,
};
