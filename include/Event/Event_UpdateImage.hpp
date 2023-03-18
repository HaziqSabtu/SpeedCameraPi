/**
 * @file Event_UpdateImage.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Update Image
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef UPDATE_IMAGE_EVENT_HPP
#define UPDATE_IMAGE_EVENT_HPP

#include <Utils/DataStruct.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

class UpdateImageEvent;
wxDECLARE_EVENT(c_UPDATE_IMAGE_EVENT, UpdateImageEvent);

/**
 * @brief Enum for Update Image Event
 * @details <table>
 * <tr>
 *    <th>Enum</th>
 *    <th>Event</th>
 * </tr>
 * <tr>
 *    <td>UPDATE_IMAGE</td>
 *    <td>Event for Signaling Update Image</td>
 * </tr>
 * <tr>
 *   <td>CLEAR_IMAGE</td>
 *   <td>Event for Signaling Clear Image</td>
 * </tr>
 * </table>
 */
enum UPDATE_IMAGE_TYPE { UPDATE_IMAGE = 1, CLEAR_IMAGE };

/**
 * @brief Custom Event for Update Image
 *
 */
class UpdateImageEvent : public wxCommandEvent {
  public:
    UpdateImageEvent(wxEventType eventType = c_UPDATE_IMAGE_EVENT, int id = 1);
    UpdateImageEvent(const UpdateImageEvent &e);
    virtual wxEvent *Clone() const;

    // Define a method to set the image data
    void SetImageData(const ImageData &imgData);

    // Define a method to get the image data
    ImageData GetImageData() const;

  private:
    ImageData imgData;
};

typedef void (wxEvtHandler::*UpdateImageFunction)(UpdateImageEvent &);
#define UpdateImageHandler(func) wxEVENT_HANDLER_CAST(UpdateImageFunction, func)
#define EVT_UPDATEIMAGE(id, func)                                              \
    wx__DECLARE_EVT1(c_UPDATE_IMAGE_EVENT, id, UpdateImageHandler(func))
#endif