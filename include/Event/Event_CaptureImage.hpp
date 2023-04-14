/**
 * @file Event_CaptureImage.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Capture Image
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CAPTURE_IMAGE_EVENT_HPP
#define CAPTURE_IMAGE_EVENT_HPP

#include <Utils/DataStruct.hpp>
#include <wx/event.h>

wxDECLARE_EVENT(c_CAPTURE_IMAGE_EVENT, wxCommandEvent);

/**
 * @brief Enum for Capture Image Event
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>CAPTURE_START</td>
 *   <td>Event for Signaling starting Capture Image</td>
 * </tr>
 * <tr>
 *   <td>CAPTURE_END</td>
 *   <td>Event for Signaling ending Capture Image</td>
 * </tr>
 * </table>
 *
 */
enum CAPTURE_IMAGE_TYPE { CAPTURE_START = 1, CAPTURE_END };

#endif