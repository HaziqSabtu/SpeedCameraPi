#pragma once

#include <wx/event.h>

/**
 * @brief Empty Event for Switch Mode
 *
 */
wxDECLARE_EVENT(c_SWITCH_MODE_EVENT, wxCommandEvent);

/**
 * @brief Enum for Switch Mode Process, Between Lane and Distance Measurement
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>SWITCH_MODE_OK</td>
 *   <td>Event for Signaling Switch Mode OK</td>
 * </tr>
 * <tr>
 *   <td>SWITCH_MODE_CANCEL</td>
 *   <td>Event for Signaling Switch Mode Cancel</td>
 * </tr>
 * <tr>
 *   <td>SWITCH_MODE_ERROR</td>
 *   <td>Event for Signaling Switch Mode Error</td>
 * </tr>
 * </table>
 *
 */
enum SWITCH_MODE_EVENT_TYPE {
    SWITCH_MODE_OK,
    SWITCH_MODE_CANCEL,
    SWITCH_MODE_ERROR
};
