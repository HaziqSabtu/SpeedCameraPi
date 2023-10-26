#pragma once

#include <wx/event.h>

/**
 * @brief Empty Event for ROI
 *
 */
wxDECLARE_EVENT(c_ROI_EVENT, wxCommandEvent);

/**
 * @brief Enum for ROI Process
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>ROI_START</td>
 *   <td>Event for Signaling Starting of ROI process</td>
 * </tr>
 * <tr>
 *   <td>ROI_END</td>
 *   <td>Event for Signaling Ending of ROI process</td>
 * </tr>
 * <tr>
 *   <td>ROI_ERROR</td>
 *   <td>Event for Signaling Error of ROI process</td>
 * </tr>
 * </table>
 *
 */
enum ROI_EVENT_TYPE {
    ROI_START = 1,
    ROI_END,
    ROI_ERROR,
};
