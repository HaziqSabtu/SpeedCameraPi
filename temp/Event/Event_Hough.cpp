/**
 * @file Event_Hough.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Hough Transform
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Event/Event_Hough.hpp>

wxDEFINE_EVENT(c_HOUGH_EVENT, HoughEvent);

/**
 * @brief Construct a new Hough Event:: Hough Event object
 *
 * @param eventType type of event to be created. Default to c_HOUGH_EVENT
 * @param id id of the event. See HOUGH_EVENT_TYPE for more info
 */
HoughEvent::HoughEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

/**
 * @brief Construct a new Hough Event:: Hough Event object
 * @details Overloaded constructor for copying event
 * This is required for data to be transported
 * @see <a href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets Event
 * Handling</a>
 *
 * @param e
 */
HoughEvent::HoughEvent(const HoughEvent &e) : wxCommandEvent(e) {
    this->SetHoughData(e.GetHoughData());
}

/**
 * @brief Clone the event
 * @details Required for sending event with wxPostEvent()
 * @see <a href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets Event
 * Handling</a>
 *
 * @return wxEvent*
 */
wxEvent *HoughEvent::Clone() const { return new HoughEvent(*this); }

/**
 * @brief Set the Hough Data object to be transported
 *
 * @param houghData the data
 */
void HoughEvent::SetHoughData(Detection::HoughData *houghData) {
    this->houghData = houghData;
}

/**
 * @brief Get the Hough Data object
 *
 * @return Detection::HoughData*
 */
Detection::HoughData *HoughEvent::GetHoughData() const { return houghData; }
