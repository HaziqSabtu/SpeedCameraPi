/**
 * @file Event_Speed.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Speed Calculation
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SPEED_CALCULATION_EVENT_HPP
#define SPEED_CALCULATION_EVENT_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

class SpeedCalcEvent;
wxDECLARE_EVENT(c_SPEED_CALC_EVENT, SpeedCalcEvent);

/**
 * @brief Enum for Speed Calculation Event
 * @details <table>
 * <tr>
 *     <th>Enum</th>
 *     <th>Event</th>
 * </tr>
 * <tr>
 *     <td>CALC_OK</td>
 *     <td>Event for Signaling Speed Calculation Success</td>
 * </tr>
 * <tr>
 *     <td>CALC_ERROR</td>
 *     <td>Event for Signaling Speed Calculation Error</td>
 * </tr>
 * </table>
 */
enum SPEED_CALC_TYPE { CALC_OK = 1, CALC_ERROR };

/**
 * @brief Custom Event for Speed Calculation
 *
 */
class SpeedCalcEvent : public wxCommandEvent {
  public:
    SpeedCalcEvent(wxEventType eventType = c_SPEED_CALC_EVENT, int id = 1);
    SpeedCalcEvent(const SpeedCalcEvent &e);
    virtual wxEvent *Clone() const;

    // Define a method to set the image data
    void SetSpeed(const double spd);

    // Define a method to get the image data
    double GetSpeed() const;

  private:
    double speed;
};

typedef void (wxEvtHandler::*CalcSpeedFunction)(SpeedCalcEvent &);
#define CalcSpeedHandler(func) wxEVENT_HANDLER_CAST(CalcSpeedFunction, func)
#define EVT_SPEED(id, func)                                                    \
    wx__DECLARE_EVT1(c_SPEED_CALC_EVENT, id, CalcSpeedHandler(func))
#endif