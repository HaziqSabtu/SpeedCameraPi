/**
 * @file Event_Hough.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Hough Transform
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef HOUGH_EVENT_HPP
#define HOUGH_EVENT_HPP

#include <wx/event.h>

class HoughEvent;
wxDECLARE_EVENT(c_HOUGH_EVENT, HoughEvent);

/**
 * @brief Enum for Hough Event
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>HOUGH_START</td>
 *   <td>Event for Signaling starting Hough Transform</td>
 * </tr>
 * <tr>
 *   <td>HOUGH_END</td>
 *   <td>Event for Signaling ending Hough Transform</td>
 * </tr>
 * </table>
 *
 */
enum HOUGH_EVENT_TYPE { HOUGH_START = 1, HOUGH_END };

/**
 * @brief Custom Event for Hough Transform
 *
 */
class HoughEvent : public wxCommandEvent {
  public:
    HoughEvent(wxEventType eventType = c_HOUGH_EVENT, int id = 1);
    HoughEvent(const HoughEvent &e);
    virtual wxEvent *Clone() const;

    void SetHoughData(Detection::HoughData *houghData);

    Detection::HoughData *GetHoughData() const;

  private:
    Detection::HoughData *houghData;
};

typedef void (wxEvtHandler::*HoughFunction)(HoughEvent &);
#define HoughHandler(func) wxEVENT_HANDLER_CAST(HoughFunction, func)
#define EVT_HOUGH(id, func)                                                    \
    wx__DECLARE_EVT1(c_HOUGH_EVENT, id, HoughHandler(func))
#endif