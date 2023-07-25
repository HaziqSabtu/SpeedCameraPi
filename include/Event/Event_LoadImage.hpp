/**
 * @file Event_LoadImage.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Load Image
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef LOAD_IMAGE_EVENT_HPP
#define LOAD_IMAGE_EVENT_HPP

#include <wx/event.h>

wxDECLARE_EVENT(c_LOAD_IMAGE_EVENT, wxCommandEvent);

/**
 * @brief Enum for Load Image Event
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>LOAD_START</td>
 *   <td>Event for Signaling starting Load Image</td>
 * </tr>
 * <tr>
 *   <td>LOAD_END_FILE</td>
 *   <td>Event for Signaling ending Load Image from File</td>
 * </tr>
 * <tr>
 *   <td>LOAD_END_CAMERA</td>
 *   <td>Event for Signaling ending Load Image from Camera</td>
 * </tr>
 * </table>
 *
 */
enum LOAD_EVENT_TYPE {
    LOAD_START_FILE = 1,
    LOAD_START_CAMERA,
    LOAD_END_FILE,
    LOAD_END_CAMERA
};

#endif