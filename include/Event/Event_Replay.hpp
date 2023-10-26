#pragma once

#include <wx/event.h>

/**
 * @brief Empty Event for Replay
 *
 */
wxDECLARE_EVENT(c_REPLAY_EVENT, wxCommandEvent);

/**
 * @brief Enum for Replay Process
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>REPLAY_START</td>
 *   <td>Event for Signaling Starting of Replay process</td>
 * </tr>
 * <tr>
 *   <td>REPLAY_END</td>
 *   <td>Event for Signaling Ending of Replay process</td>
 * </tr>
 * </table>
 *
 */
enum REPLAY_EVENT_TYPE { REPLAY_START = 1, REPLAY_END };
