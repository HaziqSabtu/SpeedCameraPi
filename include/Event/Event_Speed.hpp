#ifndef SPEED_CALCULATION_EVENT_HPP
#define SPEED_CALCULATION_EVENT_HPP

#include <Utils/DataStruct.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

class SpeedCalcEvent;
wxDECLARE_EVENT(c_SPEED_CALC_EVENT, SpeedCalcEvent);

enum SPEED_CALC_TYPE { CALC_OK = 1, CALC_ERROR };

class SpeedCalcEvent : public wxCommandEvent {
  public:
    SpeedCalcEvent(wxEventType eventType = c_SPEED_CALC_EVENT, int id = 1);
    SpeedCalcEvent(const SpeedCalcEvent &e);
    virtual wxEvent *Clone() const;

    // Define a method to set the image data
    void SetSpeed(const double &spd);

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