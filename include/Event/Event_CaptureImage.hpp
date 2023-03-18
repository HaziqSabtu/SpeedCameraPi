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

class CaptureImageEvent;
wxDECLARE_EVENT(c_CAPTURE_IMAGE_EVENT, CaptureImageEvent);

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

class CaptureImageEvent : public wxCommandEvent {
  public:
    CaptureImageEvent(wxEventType eventType = c_CAPTURE_IMAGE_EVENT,
                      int id = 1);
    CaptureImageEvent(const CaptureImageEvent &e);
    virtual wxEvent *Clone() const;

    void SetImageData(std::vector<ImageData> *imgData);

    std::vector<ImageData> *GetImageData() const;

  private:
    std::vector<ImageData> *imgData;
};

// https://docs.wxwidgets.org/3.2/overview_events.html#overview_events_custom_ownclass
typedef void (wxEvtHandler::*CaptureImageFunction)(CaptureImageEvent &);
#define CaptureImageHandler(func)                                              \
    wxEVENT_HANDLER_CAST(CaptureImageFunction, func)
#define EVT_CAPTUREIMAGE(id, func)                                             \
    wx__DECLARE_EVT1(c_CAPTURE_IMAGE_EVENT, id, CaptureImageHandler(func))
#endif