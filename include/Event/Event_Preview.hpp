#pragma once
#include <wx/event.h>

/**
 * @brief EmptyEvent for Preview with Camera
 *
 */
wxDECLARE_EVENT(c_PREVIEW_CAMERA_EVENT, wxCommandEvent);

/**
 * @brief EmptyEvent for Preview with Captured Data
 *
 */
wxDECLARE_EVENT(c_PREVIEW_CAPTURE_EVENT, wxCommandEvent);

/**
 * @brief Enum for Preview Process
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>PREVIEW_START</td>
 *   <td>Event for Signaling Starting of Preview process</td>
 * </tr>
 * <tr>
 *   <td>PREVIEW_END</td>
 *   <td>Event for Signaling Ending of Preview process</td>
 * </tr>
 * <tr>
 *   <td>PREVIEW_ERROR</td>
 *   <td>Event for Signaling Error of Preview process</td>
 * </tr>
 * </table>
 *
 */
enum PREVIEW_EVENT_TYPE { PREVIEW_START = 1, PREVIEW_END, PREVIEW_ERROR };
