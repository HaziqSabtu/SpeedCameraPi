#pragma once

#include <wx/event.h>

/**
 * @brief Empty Event for Requesting Update State
 *
 */
wxDECLARE_EVENT(c_REQUEST_UPDATE_STATE_EVENT, wxCommandEvent);

/**
 * @brief Enum for Requesting Update State Process
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>REQUEST_UPDATE_STATE</td>
 *   <td>Event for Forcing the View to update State</td>
 * </tr>
 * </table>
 *
 */
enum REQUEST_UPDATE_STATE_TYPE { REQUEST_UPDATE_STATE = 1 };
