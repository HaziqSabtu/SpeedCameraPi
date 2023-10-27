#pragma once

#include <wx/event.h>

/**
 * @brief Empty Event for Save Data
 *
 */
wxDECLARE_EVENT(c_SAVE_DATA_EVENT, wxCommandEvent);

/**
 * @brief Enum for Save Data Process
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>SAVE_DATA_START</td>
 *   <td>Event for Signaling Starting of Save Data process</td>
 * </tr>
 * <tr>
 *   <td>SAVE_DATA_END</td>
 *   <td>Event for Signaling Ending of Save Data process</td>
 * </tr>
 * <tr>
 *   <td>SAVE_DATA_ERROR</td>
 *   <td>Event for Signaling Error of Save Data process</td>
 * </tr>
 * </table>
 *
 */
enum SAVE_DATA_EVENT_TYPE {
    SAVE_DATA_START,
    SAVE_DATA_END,
    SAVE_DATA_ERROR

};
