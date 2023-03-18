/**
 * @file Event_Speed.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Speed Calculation
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Event/Event_Speed.hpp>

wxDEFINE_EVENT(c_SPEED_CALC_EVENT, SpeedCalcEvent);

/**
 * @brief Construct a new Speed Calc Event:: Speed Calc Event object
 *
 * @param eventType type of event to be created. Default to c_SPEED_CALC_EVENT
 * @param id id of the event. See SPEED_CALC_EVENT_TYPE for more info
 */
SpeedCalcEvent::SpeedCalcEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

/**
 * @brief Construct a new Speed Calc Event:: Speed Calc Event object
 * @details Overloaded constructor for copying event
 * This is required for data to be transported
 * @see <a href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets Event
 * Handling</a>
 * @param e
 */
SpeedCalcEvent::SpeedCalcEvent(const SpeedCalcEvent &e) : wxCommandEvent(e) {
    this->SetSpeed(e.GetSpeed());
}

/**
 * @brief Clone the event
 * @details Required for sending event with wxPostEvent()
 * @see <a href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets Event
 * Handling</a>
 *
 * @return wxEvent*
 */
wxEvent *SpeedCalcEvent::Clone() const { return new SpeedCalcEvent(*this); }

/**
 * @brief Set the Speed object to be transported
 *
 * @param spd the data
 */
void SpeedCalcEvent::SetSpeed(const double spd) { this->speed = spd; }

/**
 * @brief Get the Speed object
 *
 * @return double
 */
double SpeedCalcEvent::GetSpeed() const { return speed; }
