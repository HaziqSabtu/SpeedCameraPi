/**
 * @file Event_ProcessImage.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Process Image
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PROCESS_IMAGE_EVENT_HPP
#define PROCESS_IMAGE_EVENT_HPP

#include <wx/event.h>

wxDECLARE_EVENT(c_PROCESS_IMAGE_EVENT, wxCommandEvent);

/**
 * @brief Enum for Process Image Event
 * @details
 * <table>
 * <tr>
 *   <th>Enum</th>
 *   <th>Event</th>
 * </tr>
 * <tr>
 *   <td>PROCESS_BEGIN</td>
 *   <td>Event for Signaling starting Process Image</td>
 * </tr>
 * <tr>
 *   <td>PROCESS_END</td>
 *   <td>Event for Signaling ending Process Image</td>
 * </tr>
 * <tr>
 *   <td>PROCESS_ERROR</td>
 *   <td>Event for Signaling error Process Image</td>
 * </tr>
 * </table>
 *
 * */
enum PROCESS_IMAGE_TYPE { PROCESS_BEGIN = 1, PROCESS_END, PROCESS_ERROR };

#endif